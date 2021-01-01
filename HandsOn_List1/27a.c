#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    printf("Executing ls -Rl using execl()\n");
    execl("/bin/ls", "ls", "-Rl", (char *) NULL);
    return 0;
}