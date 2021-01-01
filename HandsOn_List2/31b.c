#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

union semun
{
	int val; // value for SETVAL
	struct semid_ds *buf; // buffer for IPC_Stst, IPC_SET
	unsigned short int *array; // array for GETALL, SETALL

};

int main() {

    union semun arg;
    int key, semid;

    key=ftok(".", 'c');
    semid = semget(key, 1, IPC_CREAT | 0744);
    arg.val=2;
    printf("Creating counting semaphore\n");
    /*1 for binary else >1 for Counting Semaphore */
    semctl(semid, 0, SETVAL, arg);
    printf("counting semaphore created.\n");
}