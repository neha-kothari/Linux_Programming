#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	struct itimerval timer;
    printf("Interval timer successfully set to 10secs and 10 microseconds.");
	
	timer.it_value.tv_sec = 10;
	timer.it_value.tv_usec = 10;
	timer.it_interval = timer.it_value;    
	setitimer(ITIMER_PROF, &timer, NULL);
    while(1);
	exit(EXIT_SUCCESS);
}