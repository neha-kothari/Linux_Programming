#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {

    char* const args[] = {"ls", "-Rl", (char *) NULL};
    printf("Executing ls -Rl using execv()\n");
	execv("/bin/ls", args);
    return 0;
}