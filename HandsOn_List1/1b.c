/** 1. Create the following types of a files using (i) shell command (ii) system call
 a. hard link (symlink system call)
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>    
#include <stdlib.h>    
#include <unistd.h>

int main() {

    int fd = open("sample_1b.txt", O_CREAT| O_WRONLY| O_TRUNC, 0644);
    char buffer_start[] = "Hello World! This is another dummy file :)";
    write(fd, buffer_start, sizeof(buffer_start));
    close(fd);
    char target[] = "./sample_1b.txt";
    char linkpath[] = "./hardlink_sample_1b.txt";
    int hard_link = link(target, linkpath);
    return 0;
}
