#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

    if(!fork()) {
        printf("Terminating Child process with process id : %d\n", getpid());
    }

	else
	{
		printf("pid of parent: %d\n", getpid());
		printf("Press some key to terminate parent.\n");
		getchar();
	}
	return(0);
}