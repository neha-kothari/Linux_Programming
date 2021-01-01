#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
	int pipe1[2], pipe2[2];

	pipe(pipe1);
	pipe(pipe2);
    int child1=fork();
	if(child1 == 0)
	{
		// close the read end of the pipe 1
		close(pipe1[0]);
		// duplicate write end of pipe 1 to stdout of parent
		dup2(pipe1[1], 1);
		// close read and write end of the 2nd pipe
		close(pipe2[0]);
		close(pipe2[1]);
		execlp("ls", "ls", "-l", (char *) NULL);
	}
	else
	{
		if(!fork())
		{
			dup2(pipe1[0], STDIN_FILENO);
			dup2(pipe2[1], STDOUT_FILENO);
			close(pipe1[1]);
			close(pipe2[0]);
			execlp("grep", "grep", "^d", (char *)NULL);
		}
		else
		{
			close(pipe2[1]);
			dup2(pipe2[0], STDIN_FILENO);
			close(pipe1[0]);
			close(pipe1[1]);
			execlp("wc", "wc", "-l", (char *)NULL);
		}
	}
}