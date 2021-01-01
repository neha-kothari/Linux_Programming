#include <stdio.h> 
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    clock_t t;
    t = clock();
    getpid();
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Time taken to execute getpid() is %f seconds \n", time_taken);
	return 0;
}