#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>

void signal_handler(int signal_number) {
    printf("Received SIGALRM.\n");
}

int main()
{
    struct itimerval it_val;
	if(signal(SIGALRM, signal_handler) == SIG_ERR)
		perror("signal()");
	

	// timer will expire intially after 3 second
	it_val.it_value.tv_sec = 3;
	it_val.it_value.tv_usec = 0;
	// and then at interval of 1 second every time
	it_val.it_interval.tv_sec = 1;
	it_val.it_interval.tv_usec = 0;
   if(setitimer(ITIMER_REAL, &it_val, NULL) == -1)
	{
		perror("setitimer()");
		exit(EXIT_FAILURE);
	}
    // wait for the alarm to be raised
	pause();
	exit(EXIT_SUCCESS);
}