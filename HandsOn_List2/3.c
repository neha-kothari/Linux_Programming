#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

int main()
{
	struct rlimit rlim, rlim1;
	printf("Value of core file size before changing: ");
	if(getrlimit(RLIMIT_CORE, &rlim) == -1) {
        perror("getrlimit()"); 
        exit(EXIT_FAILURE);
    } 
	printf("%lu\n", rlim.rlim_cur);
	printf("Value of core file size after changing: ");
	rlim.rlim_cur = 1024;
	if(setrlimit(RLIMIT_CORE, &rlim) == -1) {
        perror("setrlimit()"); 
        exit(EXIT_FAILURE);
    }  
	if(getrlimit(RLIMIT_CORE, &rlim1) == -1) {
        perror("getrlimit()"); 
        exit(EXIT_FAILURE);
    } 
	printf("%lu\n", rlim1.rlim_cur);
	exit(EXIT_SUCCESS);
}