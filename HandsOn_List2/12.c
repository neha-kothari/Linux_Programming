#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main()
{
	pid_t pid_child;
	if((pid_child = fork()) == -1) {
        perror("fork()");
        exit(EXIT_FAILURE);
    }
	else if(pid_child == 0)
	{
		printf("killing the parent.\n");
		printf("pid of child: %d\n", getpid());
		printf("ppid of child before killing parent: %d\n", getppid());
		if(kill(getppid(), SIGKILL) == -1) {
            perror("kill()");
            exit(EXIT_FAILURE);
        }
		sleep(1);
		printf("ppid of child after killing parent: %d\n", getppid());
		sleep(3);
		printf("Exiting child.\n");
	}
	else
	{
		printf("pid of parent: %d\n", getpid());
		sleep(3);
	}
	exit(EXIT_SUCCESS);
}