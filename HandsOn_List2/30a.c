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
	
	if((shmid = shmget(key, size, IPC_CREAT | 0744)) == -1) {
		perror("shmget()");
        exit(1);
    }
	if((data = (char*)shmat(shmid, 0, 0)) == (void*)-1)
    {
		perror("shmat()");
        exit(1);
    }

	printf("Enter the data you want to write to shared memory: ");
	scanf(" %[^\n]", data);
	printf("Data: %s\n", data);
	exit(0);
}