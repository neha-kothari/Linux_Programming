#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void signal_handler(int signal_number) {
    printf("Receieved SIGSEGV.\n");
}


int main()
{
	if(signal(SIGSEGV, signal_handler) == SIG_ERR)
		perror("signal()");
	
    
	if(kill(getpid(), SIGSEGV) == -1) 
        perror("kill()");
	
	exit(EXIT_SUCCESS);
}