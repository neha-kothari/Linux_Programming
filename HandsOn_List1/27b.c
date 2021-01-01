#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    printf("Executing ls -Rl using execlp()\n");
    execlp("ls", "ls", "-Rl", (char *) NULL);
    return 0;
}