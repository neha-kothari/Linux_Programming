#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>


union semun{
    int value;
    struct semid_ds *buf;
    unsigned short int *array;
};


int main() {

	struct ticket_st
	{
	    int ticket_number;
	}db;
	
    union semun arg;
    int key, semid;

    key = ftok(".", 112);
    semid = semget(key, 1, 0);
    if(semid==-1){
        semid = semget(key, 1, IPC_CREAT|0644);    
        arg.value = 1;
        semctl(semid, 0, SETVAL, arg);
    }

    
    printf("Before the critial section\n");

    struct sembuf sops = {0, -1, 0};
    if (semop(semid, &sops, 1) == -1) {
        perror("semop");
        exit(0);
    }
    printf("Inside the critial section\n");
	
	int fd = open("record.txt", O_CREAT|O_EXCL|O_RDWR, 0644);
    if(fd!=-1){
    	db.ticket_number = 0;
    	write(fd, &db, sizeof(db));
    }
    close(fd);


    fd = open("record.txt", O_RDWR);
    
    printf("In the critical section.\n");
	int count = read(fd, &db, sizeof(db));
	if(count == -1)
	{
		perror("read()");
		exit(EXIT_FAILURE);
	}
	
	db.ticket_number++;

	lseek(fd, 0L, SEEK_SET);
	write(fd, &db, sizeof(db));
	
	printf("New ticket number: %d\n", db.ticket_number);
	close(fd);

    printf("Press any key to exit the lock.\n");
	getchar();    



    sops.sem_op = 1;
    if (semop(semid, &sops, 1) == -1) {
        perror("semop");
        exit(0);
    }
    printf("After the critial section\n");
    return 0;
    
}