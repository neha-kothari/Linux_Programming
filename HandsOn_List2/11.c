#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

int main()
{
	struct sigaction sg;
	
	sg.sa_handler = SIG_IGN;
	if(sigaction(SIGINT, &sg, NULL) == -1) {
        perror("sigaction()");
        exit(EXIT_FAILURE);
    } 
	printf("Ignoring signal SIGINT.\n");
	sleep(5);

	printf("\nResetting to default.\n");
	sg.sa_handler = SIG_DFL;
	if(sigaction(SIGINT, &sg, NULL) == -1) {
        perror("sigaction()");
        exit(EXIT_FAILURE);
    } 
	sleep(5);

	exit(EXIT_SUCCESS);
}