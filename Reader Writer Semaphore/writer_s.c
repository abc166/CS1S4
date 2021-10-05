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

//gcc w_sempahore.c -pthread -lrt -o w_sempahore.o && ./w_sempahore.o

int main()
{
    printf("Writer Program\n\n");

    // Create/open a shared memory object
    const char *name = "/sharedmeory"; //"/myregion"
    int fileDescriptor = shm_open(name, O_CREAT | O_RDWR, 0777);

    if (fileDescriptor == -1)
    {
        printf("Creation of shared memory object failed");
        return 1;
    }
    printf("Shared memory created with file description: %d\n", fileDescriptor);

    // ftruncate returns 0 on successful set of memory object size
    if (ftruncate(fileDescriptor, sizeof(struct data)) == -1)
    {
        printf("Unable set memory object size\n");
        return 1;
    }

    // establish a mapping between a process' address space and a shared memory object,
    ptr = mmap(NULL, sizeof(struct data), PROT_READ | PROT_WRITE, MAP_SHARED, fileDescriptor, 0);
    printf("Establish a mapping to shared memory object\n");

    unsigned int shareBetweenProcess = 1;
    sem_init(&(ptr->mutex), shareBetweenProcess, 1);
    sem_init(&(ptr->rw_mutex), shareBetweenProcess, 1);
    ptr->data = ptr->reader_count = ptr->reader_number = 0;
    int x;

    while (1)
    {
        sem_getvalue(&(ptr->rw_mutex), &x);
        if (x == 0)
            printf("Writer waiting\n\n");

        sem_wait(&(ptr->rw_mutex));
        ptr->data++;
        printf("Writer modified data to %d\n", ptr->data);
        sem_post(&(ptr->rw_mutex));
        sleep(1);
    }
}
