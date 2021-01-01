#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main()
{
    long val;
    if((val = sysconf(_SC_PHYS_PAGES)) == -1) {
        perror("sysconf");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Total number of pages in the physical memory: %ld\n", val);
    }
    
}