#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>

int main() {

    int fd = open("dummy12.txt", O_CREAT | O_RDONLY | O_EXCL, 0644);
	if(fd < 0) perror("open()");
	int flag_val = fcntl(fd, F_GETFL);
	if(flag_val < 0) perror("fcntl()");

	printf("Opening mode: ");
	
	if((flag_val & O_ACCMODE) == O_RDONLY) 
		printf("Read Only\n");

	if((flag_val & O_ACCMODE) == O_WRONLY) 
		printf("Write Only\n");
	
	if((flag_val & O_ACCMODE) == O_RDWR)
		printf("Read & Write\n");
	if(close(fd) < 0)
	{
		perror("close()");
	}
    return 0;
}