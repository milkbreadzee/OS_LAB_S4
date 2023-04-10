#include<stdio.h>  
#include<stdlib.h>  
#include<unistd.h>  // for read() 
#include<sys/shm.h>  // for shmget(), shmat(), shmdt(),shmctl()
#include<string.h>  
int main()  
{  
int i;  
void *shared_memory;  
void *p2shared_memory;  
char buff[100];  
int shmid;  
//key_t is a datatype
// 0666 -
//  0 prefix = number is in octal format
//  666 = -rw-rw-rw- (666) -- Everyone can read and write to the file. Bad idea. 
shmid=shmget((key_t)2345, 1024, 0666|IPC_CREAT);   
//creates shared memory segment with key 2345, having size 1024 bytes.
// IPC_CREAT is used to create the shared segment if it does not exist. 
// 0666 are the permissions on the shared segment .
// IPC_EXCL: This flag is used with IPC_CREAT to ensure that the shared memory segment is only created if it doesn't already exist.
// syntax :  int shmflg = IPC_CREAT | IPC_EXCL | 0666;
printf("Key of shared memory is %d\n",shmid);  
shared_memory=shmat(shmid,NULL,0);   
//process attached to shared memory segment  
printf("Process attached at %p\n",shared_memory);   
//this prints the address where the segment is attached with this process  
printf("Enter some data to write to shared memory\n");  
read(0,buff,100); //get some input from user  
strcpy(shared_memory,buff); //data written to shared memory  
printf("You wrote : %s\n",(char *)shared_memory);  
// int p2_shmid=shmget((key_t)2345, 1024, 0666);
// p2shared_memory = shmat(p2_shmid, NULL, 0);
// printf("Process attached at %p\n",p2shared_memory);  
// printf("Data read from shared memory is : %s\n",(char *)p2shared_memory);  
}  