#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>

int main() {

    int fd = open("file_10_dummy.txt", O_CREAT | O_RDWR | O_EXCL, 0644);
	if(fd < 0) perror("open()");
    if(write(fd, "HelloWorld", 10) < 0) {
         perror("write()");
    }
    int return_val = lseek(fd, 10, SEEK_CUR);
    if(return_val < 0) { perror("lseek()"); }
    printf("The return value of lseek() = %d\n", return_val);
    if(write(fd, "HiWorld!!!", 10) < 0) perror("write()");
    return 0;
}