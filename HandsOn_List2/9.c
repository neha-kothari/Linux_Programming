#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main()
{
	printf("Ignoring the SIGINT signal.\n");
	if(signal(SIGINT, SIG_IGN) == SIG_ERR) {
        perror("signal()");
        exit(EXIT_FAILURE);
    } 
	sleep(5);
	printf("\nResetting to default.\n");
	if(signal(SIGINT, SIG_DFL) == SIG_ERR) {
        perror("signal()");
        exit(EXIT_FAILURE);
    } 
	sleep(5);
	exit(EXIT_SUCCESS);
}