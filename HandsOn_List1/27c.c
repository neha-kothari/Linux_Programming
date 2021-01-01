#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    printf("Executing ls -Rl using execle()\n");
    execle("/bin/ls", "ls", "-Rl", (char *) NULL, (char *) NULL);
    return 0;
}