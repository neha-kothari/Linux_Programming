#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	int cur_priority = getpriority(PRIO_PROCESS, 0);

	printf("Priority of the current process: %d\n", cur_priority);
	
	// nice sys call increment the priority of the process by the given value
	nice(3);
	cur_priority = getpriority(PRIO_PROCESS, 0);
	
	printf("Priority after nice function call: %d\n", cur_priority);
	// set the priority to the given priority ret 0 on success and
	// -1 on failure
	if(setpriority(PRIO_PROCESS, 0, 11) == -1)
	{
		perror("setpriority()");
		exit(EXIT_FAILURE);
	}
	cur_priority = getpriority(PRIO_PROCESS, 0);
	
	printf("Priority after setpriority function call: %d\n", cur_priority);
	return 0;
}