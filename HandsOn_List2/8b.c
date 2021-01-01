#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void signal_handler(int signal_number) {
    printf("Received SIGINT.\n");
}


int main()
{
	if(signal(SIGINT, signal_handler) == SIG_ERR)
		perror("signal()");
	
    
	if(kill(getpid(), SIGINT) == -1) 
        perror("kill()");
	
	exit(EXIT_SUCCESS);
}