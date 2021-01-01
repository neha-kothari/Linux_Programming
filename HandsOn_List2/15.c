#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    char buf[10];
    pipe(fd);

    if(!fork()) {
        close(fd[1]);
        printf("This is child with pid = %d and it's reading\n",getpid());
        read(fd[0],buf, 10);
        printf("buf=%s\n", buf);
    } else {
        close(fd[0]);
        printf("This is parent with pid = %d and it's writing\n", getpid());
        write(fd[1], "HelloWorld\n", 10);        
        wait(0);
    }

    return 0;
}