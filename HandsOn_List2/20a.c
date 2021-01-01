#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main() {
    char buf[100];
    int fd = mkfifo("myfifo20", 0744);
    fd = open("myfifo20", O_WRONLY);
    printf("Enter the text: ");
    scanf(" %[^\n]", buf);
    write(fd, buf, sizeof(buf));
}