#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	printf("Caught SIGFPE signal.\n");
}

int main(int argc, char const *argv[])
{
	struct sigaction sg;
	sg.sa_sigaction = signal_handler;
	if(sigaction(SIGFPE, &sg, NULL) == -1) {
        perror("sigaction()");
        exit(EXIT_FAILURE);
    }
	if(kill(getpid(), SIGFPE) == -1) {
        perror("kill()");
        exit(EXIT_FAILURE);
    }
	exit(EXIT_SUCCESS);
}