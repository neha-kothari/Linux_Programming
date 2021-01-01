#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	
	int fd = open("record.txt", O_RDWR);
	if(fd == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	if(fcntl(fd, F_SETLKW, &lock)< 0)
	{
		perror("fcntl()");
		exit(EXIT_FAILURE);
	}
    printf("Read lock is aquired.\n");
	printf("In the critical section.\n");
	printf("Press any key to increment ticket number and exit the lock.\n");
	getchar();
	struct ticket_st
	{
		long long int ticket_number;
	}db;
	int count = read(fd, &db, sizeof db);
	if(count == -1)
	{
		perror("read()");
		exit(EXIT_FAILURE);
	}
	
	db.ticket_number++;

	lseek(fd, 0L, SEEK_SET);
	write(fd, &db, sizeof db);

	printf("Incremented successfully.\n");
	printf("New ticket number: %lld\n", db.ticket_number);

	lock.l_type = F_UNLCK;
	if(fcntl(fd, F_SETLKW, &lock))
	{
		perror("fcntl()");
		exit(EXIT_FAILURE);
	}
    printf("Unlocked the file.\n");
	close(fd);
	return 0;
}