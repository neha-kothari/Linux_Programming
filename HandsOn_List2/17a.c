#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR_EXIT(msg) do{perror(msg);exit(EXIT_FAILURE);}while(0)

int main()
{
	int fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();
	if(pid == 0)
	{
		//closing stdout fd
		close(STDOUT_FILENO);
		// closing read end of the pipe
		close(fd[0]) ;
		// duplicating fd[1] with least number available
		// that is of STDOUT
		dup(fd[1]);
		// executing `ls -lh` and the output goes to the pipe
		// since it is performing as stdout
		execlp("ls", "ls", "-lh", (char *) NULL);
	}
	else
	{
		//closing stdin
		close(STDIN_FILENO);
		// closing write end of the pipe
		close(fd[1]);
		// fd[0] will now work as STDIN
		dup(fd[0]);
		execlp("wc", "wc", (char *) NULL);
	}
}