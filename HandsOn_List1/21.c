#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	if(!fork())
	{
		printf("Process id of child: %d\n", getpid());
	}
	else
	{
		printf("Process id of parent: %d\n", getpid());
	}
	return 0;
}
