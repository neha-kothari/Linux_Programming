#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>
#include <string.h>
int main() {
    char buf[100];
    int n;
    n=read(0, buf, sizeof(buf));
    write(1, buf, n);
    return 0;
}