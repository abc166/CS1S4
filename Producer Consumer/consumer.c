#include<stdio.h>
#include<semaphore.h>
#include <stdlib.h>
#include<unistd.h>
#include <fcntl.h> 
#include <sys/mman.h>
#include<sys/stat.h>

struct data{
  int a[5];
  sem_t full,empty,mutex;
}*d;
int main(){
  int x,out=0,ch,i,n;
  int fd=shm_open("/shared",O_CREAT|O_RDWR,0777);
  ftruncate(fd,sizeof(struct data));
  d=mmap(NULL,sizeof(struct data),PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
  
  printf("Enter no of processes to be consumed:");
  scanf("%d",&n);
  for(i=0;i<n;i++){
    sem_getvalue(&(d->empty),&x);
    if(x==5)
      printf("Buffer empty\n");
    else{
      sem_wait(&(d->mutex));
      sem_wait(&(d->full));
      while(d->a[out]==0)
      {
          out=(out+1)%5;
      }
      ch=d->a[out];
      printf("Item consumed:%d\n",ch);
      d->a[out]=0;
      out=(out+1)%5;
      sem_post(&(d->mutex));
      sem_post(&(d->empty));
    }
  }
}