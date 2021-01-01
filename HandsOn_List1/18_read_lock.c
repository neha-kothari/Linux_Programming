/*	Write a program to perform Record locking.
	a. Implement write lock
	b. Implement read lock
	Create three records in a file. Whenever you access a particular record, first lock it then modify/access
	to avoid race condition.
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
	int fd;
	fd = open("18_dummy.txt", O_RDWR | O_CREAT, 0666);
	struct flock lock;

	int ch;
	printf("Enter the record(1, 2, 3) to be read:");
	scanf("%d", &ch);

	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = ((ch -1)*20) + 1;
	lock.l_len = 20;
	lock.l_pid = getpid();

	printf("Read Lock \n");
	int ret = fcntl(fd, F_SETLKW, &lock);
	char text[20];
	int off = lseek(fd, ((ch -1 )*20), SEEK_SET);
	pread(fd, text, sizeof(text),off);
    printf("Read lock is aquired.\n");
	printf("In the critical section.\n");
	printf("Press any key to exit the lock.\n");
    getchar();
	getchar();
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
  printf("data you want to read is : %s\n",text);
  printf("Lock released!\n");

  close(fd);
	return 0;

}