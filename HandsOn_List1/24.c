#include <stdio.h>
#include <unistd.h>

int main() {
    if(!fork()) {

        printf("Child ppid before orphan: %d\n", getppid());
        sleep(3);
        printf("Child ppid after sleep: %d\n", getppid());

    } else {
        printf("pid of parent: %d\n", getpid());
        sleep(1);
    }
    return 0;
}