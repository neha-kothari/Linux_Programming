#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd1[2], fd2[2];
    char buf1[11], buf2[12];
    pipe(fd1);
    pipe(fd2);
    if(!fork()) {
        close(fd2[0]);
        close(fd1[1]);
        printf("This is child with pid = %d and it's reading from pipe1\n",getpid());
        read(fd1[0],buf1, 10);
        printf("Read data=%s\n", buf1);
        printf("This is child with pid = %d and it's writing into pipe2\n",getpid());
        write(fd2[1], "HelloParent\n", 11);  
        //printf("buf=%s\n", buf1);
    } else {
        close(fd1[0]);
        close(fd2[1]);
        printf("This is parent with pid = %d and it's writing into pipe1\n", getpid());
        write(fd1[1], "HelloChild\n", 10);  
        wait(0);
        printf("This is parent with pid = %d and it's reading from pipe2\n", getpid());      
        read(fd2[0],buf2, 11);
        printf("read data=%s\n", buf2);
        
    }

    return 0;
}