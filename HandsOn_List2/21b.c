#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	char bufr[512], bufw[512];

	int fdr = open("21a_fifoFile", O_RDONLY);
    int fdw = open("21b_fifoFile", O_WRONLY);
    printf("Enter the text in Pipe2: ");
    scanf(" %[^\n]", bufw);
    write(fdw, bufw, sizeof(bufw));
    read(fdr, bufr, sizeof(bufr));
    printf("The text from Pipe1: %s", bufr);
    close(fdw);
    close(fdr);
}