#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signal_number) {
    printf("Received SIGVTALRM.\n");
}


int main()
{
	struct itimerval timer;
	if(signal(SIGVTALRM, signal_handler) == SIG_ERR)
	{
		perror("signal()");
		exit(EXIT_FAILURE);
	}

	// timer will expire intially after 3 second
	timer.it_value.tv_sec = 3;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = 1; 
    timer.it_interval.tv_usec = 0; 
	if(setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1)
	{
		perror("setitimer()");
		exit(EXIT_FAILURE);
	}
    while(1);
	exit(EXIT_SUCCESS);
}