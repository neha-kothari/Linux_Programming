#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>
#include <stdlib.h>

int main() {

    char buf[2048];
    int s;
    int fd = open("file_s.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open()");
		exit(1);
	}

    while(read(fd, buf, 1)) {
        if(buf[0] == '\n') getchar();
		else printf("%c", buf[0]);
    }

    return 0;
}