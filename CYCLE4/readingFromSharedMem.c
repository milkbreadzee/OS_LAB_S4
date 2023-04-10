#include<stdio.h>  
#include<stdlib.h>  
#include<unistd.h>  // for read() 
#include<sys/shm.h>  // for shmget(), shmat(), shmdt(),shmctl()
#include<string.h>  
int main()  
{  
int i;  
void *p2shared_memory;  
char buff[100];  
int shmid;  
int p2_shmid=shmget((key_t)2345, 1024, 0666);
p2shared_memory = shmat(p2_shmid, NULL, 0);
printf("Process attached at %p\n",p2shared_memory);  
printf("Data read from shared memory is : %s\n",(char *)p2shared_memory);  
}  