#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void signal_handler(int signal_number) {
    printf("Received SIGALRM.\n");
}

int main()
{
	if(signal(SIGALRM, signal_handler) == SIG_ERR)
		perror("signal()");
	
    //raise the alarm after 2 seconds
	alarm(2);
    // wait for the alarm to be raised
	pause();
	exit(EXIT_SUCCESS);
}