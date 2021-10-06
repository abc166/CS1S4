#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<semaphore.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/stat.h>

struct data{
sem_t mutex,wrt;
int no;
}*d;

void main(){
  int x,in=0;
  int fd=shm_open("/shared",O_CREAT|O_RDWR,0777);
  ftruncate(fd,sizeof(struct data));
  d=mmap(NULL,sizeof(struct data),PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
  sem_init(&(d->mutex),10,1);
  
  sem_init(&(d->wrt),10,1);

  printf("enter th data to be written: ");
  scanf("%d",&(d->no));

  sem_wait(&(d->wrt));
  printf("%d data written",(d->no));
  sem_post(&(d->wrt));
}