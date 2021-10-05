#include <fcntl.h> // o flags of shm_open()
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>   // for rand()
#include <sys/mman.h> // shm_open(),mmap()
#include <unistd.h>   //ftruncate()

//sem_init() -pthread
//shm_open() -lrt

struct data
{
    int data;
    int reader_count;
    int reader_number; //Just to print which reader it is now
    sem_t mutex, rw_mutex;
} * ptr;

//gcc r_sempahore.c -pthread -lrt -o r_sempahore.o && chmod +x r.sh && ./r.sh

int main()
{
    // Create/open a shared memory object
    const char *name = "/sharedmeory"; //"/myregion"
    int fileDescriptor = shm_open(name, O_CREAT | O_RDWR, 0777);

    if (fileDescriptor == -1)
    {
        printf("Creation of shared memory object failed");
        return 1;
    }

    // ftruncate returns 0 on successful set of memory object size
    if (ftruncate(fileDescriptor, sizeof(struct data)) == -1)
    {
        printf("Unable set memory object size\n");
        return 1;
    }

    ptr = mmap(NULL, sizeof(struct data), PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, 0);

    //Reader
    sem_wait(&(ptr->mutex));
    ptr->reader_count++;
    int reader_no = ++ptr->reader_number;
    if (ptr->reader_count == 1)
    {
        sem_wait(&(ptr->rw_mutex));
        sleep(2); //TO keep writer waiting just for displaying
    }
    sem_post(&(ptr->mutex));

    printf("Reader %d: read data as %d\n", reader_no, ptr->data);

    sem_wait(&(ptr->mutex));
    ptr->reader_count--;
    if (ptr->reader_count == 0)
    {
        sem_post(&(ptr->rw_mutex));
    }
    sem_post(&(ptr->mutex));
}
