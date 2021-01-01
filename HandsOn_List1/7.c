#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>
#include <stdlib.h>

int main() {

    char buf[2048];
    int s;
    int fd_s = open("file_s.txt", O_RDONLY);
	int fd_d = open("file_d.txt", O_CREAT | O_WRONLY | O_EXCL, 0644);
	if (fd_s < 0 || fd_d < 0)
	{
		perror("open()");
		exit(1);
	}

	// copy the file from source file to destination file
	s = read(fd_s, buf, sizeof(buf));
	if(write(fd_d, buf, s) == -1)
	{
		perror("write()");
		exit(1);
	}	
	return 0;
}