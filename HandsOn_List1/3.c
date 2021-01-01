#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main() {
    int fd;
    fd = creat("sample3", 0644);
    printf("File descriptor value = %d\n", fd);
    if(fd==-1) {
        perror("Error");
    }
    return 0;
}