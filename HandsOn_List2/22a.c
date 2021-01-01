#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main() {
	int fd = mkfifo("22_fifoFile", 0744);
	fd = open("22_fifoFile", O_NONBLOCK | O_RDONLY);
	char buf[512];
	fd_set rfds;
	struct timeval tv;
	int retval;
	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);
	tv.tv_sec = 10;tv.tv_usec = 0;
	if(select(4, &rfds, NULL, NULL, &tv)) {
		read(fd, buf, sizeof(buf));
		printf("%s", buf);
	} else {
        printf("Failed to get the data in 10 seconds");
    }
		close(fd);
}