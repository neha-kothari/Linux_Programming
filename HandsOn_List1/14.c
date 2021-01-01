#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	struct stat stats;
	if(lstat(argv[1], &stats) == -1) perror("lstat()");
	printf("File type: ");

	switch(stats.st_mode & S_IFMT)
	{
		case S_IFBLK: printf("block device\n"); break;
		case S_IFCHR: printf("character device\n"); break;
		case S_IFDIR: printf("directory\n"); break;
		case S_IFIFO: printf("FIFO/pipe\n"); break;
		case S_IFLNK: printf("symlink\n"); break;
		case S_IFREG: printf("regular file\n"); break;
		case S_IFSOCK: printf("socket\n"); break;
		default:	  printf("Unknown\n");
	}
	exit(EXIT_SUCCESS);
}