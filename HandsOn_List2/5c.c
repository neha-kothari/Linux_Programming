#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main()
{
    long val;
    if((val = sysconf(_SC_CLK_TCK)) == -1) {
        perror("sysconf");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Number of clock ticks (jiffy) per second.: %ld\n", val);
    }
    
}