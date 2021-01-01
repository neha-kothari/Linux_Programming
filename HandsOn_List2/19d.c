#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd = mknod("myfifo_mknod", S_IFIFO|0744, 0);
    //mknod is a system call
    printf("FD of pipe = %d\n", fd);
    return 0;
}