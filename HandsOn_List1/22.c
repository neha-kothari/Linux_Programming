#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = open("22.txt", O_WRONLY | O_CREAT, 0644);
	if(!fork())
	{
		write(fd, "Child writing\n", 14);
	}
	else
	{
		write(fd, "Parent writing\n", 15);
	}
	return 0;
}
