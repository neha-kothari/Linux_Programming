#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>

int main() {

    int fd, dup_return;
    char buf[] = "Random stuff\n";
    fd = open("dummy11c.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    printf("Duplicating the file descriptor using dup for file descriptor %d\n", fd);
    int fd3 = fcntl(fd, F_DUPFD, fd);
    if (fd3 < 0) perror("fcntl(fd, F_DUPFD, fd)");
    printf("fd3 is: %d\n", fd3);
    if(write(fd3, "Written using fd3 duplicate fd created by fcntl().\n", 51) < 0)
        perror("write()");
    
    return 0;
}