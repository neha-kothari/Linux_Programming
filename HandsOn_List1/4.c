#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>

int main() {

    int fd1, fd2;
    fd1 = open("sample3", O_RDWR);
    close(fd1);
    fd2 = open("file2", O_CREAT | O_RDWR | O_EXCL, 0644);
    if(fd2==-1) {
        perror("Error");
    }
    return 0;
}