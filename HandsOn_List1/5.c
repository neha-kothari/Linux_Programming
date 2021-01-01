
#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>
#include <stdlib.h>
int main() {
    int flags = O_RDWR | O_CREAT;
	int mode = 0644;
	int fd1 = open("file1_5", flags, mode);
	int fd2 = open("file2_5", flags, mode);
	int fd3 = open("file3_5", flags, mode);
	int fd4 = open("file4_5", flags, mode);
	int fd5 = open("file5_5", flags, mode);
	if(fd1 < 0 || fd2 < 0 || fd3 < 0 || fd4 < 0 || fd5 < 0)
	{
		perror("open()");
	}
	printf("File descriptor of the opened file1_5: %d\n", fd1);
	printf("File descriptor of the opened file2_5: %d\n", fd2);
	printf("File descriptor of the opened file3_5: %d\n", fd3);
	printf("File descriptor of the opened file4_5: %d\n", fd4);
	printf("File descriptor of the opened file5_5: %d\n", fd5);
	while(1);

    return 0;

}