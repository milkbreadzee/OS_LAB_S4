#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fcntl.h>
// #include <sys/stat.h>
#include <semaphore.h>

#define SHM_SIZE 10
#define EMPTY_SEM "/empty"
#define FULL_SEM "/full"
#define MUTEX_SEM "/mutex"

int main() {
    int shmid;
    int *buffer;
    sem_t *empty_sem, *full_sem, *mutex_sem;
    pid_t pid;
    int i, j;

    // Create shared memory segment
    if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE * sizeof(int), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach to shared memory segment
    //turning -1 into a pointer otherwise, it will be a comparison btw an intger and a pointer.
    if ((buffer = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    // Create semaphores
    //four arguments: a string containing the name of the semaphore,
    // a flag indicating whether the semaphore is to be created (O_CREAT) or opened (O_CREAT | O_EXCL), 
    //a file mode (0644 is common), and an initial value for the semaphore.
    //On error, sem_open() returns SEM_FAILED, with errno set to indicate the error.
    //Notice that the question code neglected to use SEM_FAILED; but rather specified '-1'; which resulted in the compiler warning "comparison between pointer and integer" indicated in the question.
    //sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);
    // ref: https://man7.org/linux/man-pages/man3/sem_open.3.html
    if ((empty_sem = sem_open(EMPTY_SEM, O_CREAT, 0644, SHM_SIZE)) == SEM_FAILED) {
        perror("sem_open error at EMPTY_SEM");
        exit(1);
    }
    if ((full_sem = sem_open(FULL_SEM, O_CREAT, 0644, 0)) == SEM_FAILED) {
        perror("sem_open error at FULL_SEM");
        exit(1);
    }
    if ((mutex_sem = sem_open(MUTEX_SEM, O_CREAT, 0644, 1)) == SEM_FAILED) {
        perror("sem_open error at MUTEX_SEM");
        exit(1);
    }

    // Create producer process
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        //implies the current process is the child proccess
        for (i = 0; i < 10; i++) {
            int valuep; 
            sem_getvalue(mutex_sem, &valuep); 
            printf("The value of the semaphors is (before producer got in) %d\n", valuep);
            sem_wait(empty_sem);
            sem_wait(mutex_sem);
            sem_getvalue(mutex_sem, &valuep); 
            printf("The value of the semaphors is (after producer got in) %d\n", valuep);
            buffer[i % SHM_SIZE] = i;
            printf("Producer produced item %d\n", i);
            sem_post(mutex_sem);
            sem_post(full_sem);
            sem_getvalue(mutex_sem, &valuep); 
            printf("The value of the semaphors is (after producer left) %d\n", valuep);
            usleep(100000);
        }
        exit(0); //program termintated succesfully
    }

    // Create consumer process
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        for (j = 0; j < 10; j++) {
            int valuec; 
            sem_getvalue(mutex_sem, &valuec); 
            printf("The value of the semaphors is (before consumer got in) %d\n", valuec);
            sem_wait(full_sem);
            sem_wait(mutex_sem);
            sem_getvalue(mutex_sem, &valuec); 
            printf("The value of the semaphors is (after consumer got in) %d\n", valuec);
            printf("Consumer consumed item %d\n", buffer[j % SHM_SIZE]);
            sem_post(mutex_sem);
            sem_post(empty_sem);
            sem_getvalue(mutex_sem, &valuec); 
            printf("The value of the semaphors is (after consumer left) %d\n", valuec);
            usleep(200000);
        }
        exit(0);
    }

    // Wait for child processes to finish
    wait(NULL);
    wait(NULL);

    // Remove shared memory segment and semaphores
    shmdt(buffer);
    shmctl(shmid, IPC_RMID, NULL);
    sem_unlink(EMPTY_SEM);
    sem_unlink(FULL_SEM);
    sem_unlink(MUTEX_SEM);

    return 0;
}