#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>
union semun
{
	int val; // value for SETVAL
	struct semid_ds *buf; // buffer for IPC_Stst, IPC_SET
	unsigned short int *array; // array for GETALL, SETALL

};
int main() {

    union semun arg;
    int fd = open("record.txt", O_RDWR);
    int key=ftok(".", 112);    
    int semid = semget(key, 1, 0);
    struct sembuf buf = {0,-1,0};
    /*1 for binary else >1 for Counting Semaphore */
    printf("Deleting binary semaphore\n");
    semctl(semid, 0, IPC_RMID, arg);
    printf("Deleting counting semaphore\n");
    key=ftok(".", 123);    
    semid = semget(key, 1, 0);
    semctl(semid, 0, IPC_RMID, arg);
    key=ftok(".", 113);    
    semid = semget(key, 1, 0);
    semctl(semid, 0, IPC_RMID, arg);
}