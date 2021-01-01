#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();
	if(pid == 0)
	{
		// closing read end of the pipe
		close(fd[0]);
		// closing STDOUT and assigning it to the fd[1]
		dup2(fd[1], STDOUT_FILENO);
		// executing `ls -lh` and the output goes to the pipe
		// since it is performing as stdout
		execlp("ls", "ls", "-lh", (char *) NULL);
	}
	else
	{
		// closing write end of the pipe
		close(fd[1]);
		// fd[0] will now work as STDIN
		dup2(fd[0], STDIN_FILENO);
		execlp("wc", "wc", (char *) NULL);
	}
}