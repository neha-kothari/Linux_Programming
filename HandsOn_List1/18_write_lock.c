#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	
	int fd = open("18_dummy.txt", O_RDWR | O_CREAT, 0766);
	char s1[20] = "first entry\n";
	char s2[20] = "second entry\n";
	char s3[20] = "third entry\n";
    char s4[20]  = "Updated Line.\n";

	if(fd != -1){
		write(fd, s1, 20);
		write(fd, s2, 20);
		write(fd, s3, 20);

		int size = 20, ch;
		printf("Enter the record to be modified(1, 2, 3): \n");
		scanf("%d", &ch);
        struct flock lock;
	    lock.l_type = F_WRLCK;
	    lock.l_whence = SEEK_SET;
	    lock.l_start = ((ch -1)*20) + 1;
	    lock.l_len = 20;
	    lock.l_pid = getpid();
		printf("Aquiring write lock.\n");
	    printf("l_start: %ld and l_len: %ld\n", lock.l_start, lock.l_len);
		fcntl(fd, F_SETLKW, &lock);        

        printf("Write lock is aquired.\n");
	    printf("In the critical section.\n");
	    printf("Press any key to exit the lock.\n");
	    getchar();
        getchar();
        int off =lseek(fd, ((ch -1 )*20), SEEK_SET);
		pwrite(fd, s4, 20,off);
        printf("written successful\n");
		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);

		printf("Unlocked the file.\n");

	}
	else
		perror("Lock Error:");

		close(fd);
return 0;
	
}