#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	int shmid;
	size_t size = 1024;
	key_t key = ftok(".", 'a');
	char *data;	
	

	if((shmid = shmget(key, size, 0744| IPC_CREAT)) == -1) {
        perror("shmget()");
        exit(1);
    }
	if((data = (char*)shmat(shmid, NULL, 0)) == (void*)-1) {
        perror("shmat()");
        exit(1);
    }
	printf("Data: %s\n", data);
	if(shmdt(data) == -1) {
        perror("shmdt()");
        exit(1);
    }
	if((shmctl(shmid, IPC_RMID, NULL)) == -1) {
        perror("shmctl()");
        exit(1);
    }
}