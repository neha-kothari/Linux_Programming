#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];
    char buf[10];
    printf("Creating a pipe\n");
    pipe(fd);
    //getchar();
    printf("Writing to the pipe\n");
    write(fd[1], "HelloWorld\n", 10);
    close(fd[1]);
    printf("Reading from the pipe\n");
    read(fd[0], buf, 10);
    close(fd[0]);
    printf("Displaying : buf=%s\n", buf);
    return 0;
}