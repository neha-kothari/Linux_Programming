#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void signal_handler(int signal_number) {
    printf("Received SIGFPE.\n");
}


int main()
{
	if(signal(SIGFPE, signal_handler) == SIG_ERR)
		perror("signal()");
	
    
	if(kill(getpid(), SIGFPE) == -1) 
        perror("kill()");
	
	exit(EXIT_SUCCESS);
}