#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main()
{
    long val;
    if((val = sysconf(_SC_PAGESIZE)) == -1) {
        perror("sysconf");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Size of a page: %ld\n", val);
    }
    
}