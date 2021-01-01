#include <stdio.h>
#include <sched.h>
#include <stdlib.h>

int main()
{
	int priority;
	priority = sched_get_priority_min(SCHED_RR);
	printf("Min priority: %d\n", priority);
	priority = sched_get_priority_max(SCHED_FIFO);
	printf("Max priority: %d\n", priority);
	return 0;
}