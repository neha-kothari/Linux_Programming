#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
 
int main()
{
	printf("Before changing the policy process is using ");
    int policy = sched_getscheduler(getpid());
	printf("Current policy: %d\n", policy);
	struct sched_param param;
	param.sched_priority = 1;   
	sched_setscheduler(0, SCHED_FIFO, &param) ;
    int policy1 = sched_getscheduler(getpid());
	printf("After changing the policy process is using %d\n", policy1);
	return 0;
}