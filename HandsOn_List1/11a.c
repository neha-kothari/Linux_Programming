#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>


int main() {
    int fd, dup_return;
    char buf[] = "Random stuff\n";
    fd = open("dummy11a.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    printf("Duplicating the file descriptor using dup for file descriptor %d\n", fd);
    dup_return = dup(fd);
    printf("dup return value is %d\n", dup_return);
    write(fd, buf, sizeof(buf)-1);
    write(dup_return, "writing this using dup", 22);

    close(fd);
    return 0;
}