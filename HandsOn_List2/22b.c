#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	
	int fd = open("22_fifoFile", O_WRONLY);
	write(fd, "Hello!!", sizeof("Hello!!"));
	close(fd);

}