#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>

int main() {
    int file_desc = open("11b.txt", O_CREAT | O_WRONLY | O_APPEND, 0755);
    //here the newfd is the file descriptor of stdout (i.e. 1)
    dup2(file_desc, 1);
    //All the printf statements will be written in the file 11b.txt
    printf("I will be printed in the file 11b.txt");
}