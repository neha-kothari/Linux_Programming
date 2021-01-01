#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();
	if(pid == 0) {
		//closing stdout fd
		close(STDOUT_FILENO);
		// closing read end of the pipe
		close(fd[0]);
		// duplicating fd[1] with STDOUT now 1 will have the same
		// pipe file opened as fd[1]
		int tfd = fcntl(fd[1], F_DUPFD, STDOUT_FILENO);
		// fd[1] can be closed as file descriptor 1 has this value
		close(fd[1]);
		// executing `ls -lh` and the output goes to the pipe
		// since it is performing as stdout
		execlp("ls", "ls", "-lh", (char *) NULL);
	}
	else {
		//closing stdin
		close(STDIN_FILENO);
		// closing write end of the pipe
		close(fd[1]);
		// fd[0] will now work as STDIN
		int tfd = fcntl(fd[0], F_DUPFD, STDIN_FILENO);
		execlp("wc", "wc", (char *) NULL);
	}
}