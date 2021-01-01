#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    
    char buf[100];
    int fd = open("myfifo20", O_RDONLY);
    read(fd, buf, sizeof(buf));
    printf("The text from FIFO: %s\n", buf);
}