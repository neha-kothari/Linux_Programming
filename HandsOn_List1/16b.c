
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd = open("sample3", O_RDWR);
	
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	// for advisory file locking both should be 0
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	printf("Aquiring lock.\n");
	if(fcntl(fd, F_SETLKW, &lock))
	{
		perror("fcntl()");
		exit(EXIT_FAILURE);
	}
	printf("Read lock is aquired.\n");
	printf("In the critical section.\n");
	printf("Press any key to exit the lock.\n");
	getchar();
	lock.l_type = F_UNLCK;
	if(fcntl(fd, F_SETLKW, &lock))
	{
		perror("fcntl()");
		exit(EXIT_FAILURE);
	}
	printf("Unlocked the file.\n");
	close(fd);
	exit(EXIT_SUCCESS);
}