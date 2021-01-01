#include <unistd.h>
#include <stdio.h>
int main() {
    long PIPE_BUF, OPEN_MAX;
    PIPE_BUF = pathconf(".", _PC_PIPE_BUF);
    OPEN_MAX = sysconf(_SC_OPEN_MAX);
    printf("Maximum number of files can be opened within a process = %ld\t", OPEN_MAX);
    printf("\nMaximum size of a pipe of FIFO (circular buffer) = %ld\t", PIPE_BUF);
    return 0;
}