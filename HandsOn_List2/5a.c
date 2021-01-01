#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main()
{
	long val;
	if((val = sysconf(_SC_ARG_MAX)) == -1) {
        perror("sysconf");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Maximum length of the arguments to the exec family of functions: %ld\n", val);
    }
    
    exit(EXIT_SUCCESS);
}