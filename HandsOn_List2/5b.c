#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main()
{
    long val;
    if((val = sysconf(_SC_CHILD_MAX)) == -1) {
        perror("sysconf");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Maximum number of simultaneous process per user id: %ld\n", val);
    }
    
}