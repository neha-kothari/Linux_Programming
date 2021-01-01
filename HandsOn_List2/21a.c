#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fdw = mkfifo("21a_fifoFile", 0755);
    int fdr = mkfifo("21b_fifoFile", 0755);
	char bufr[512], bufw[512];
    printf("Enter the text in Pipe1: ");
    scanf(" %[^\n]", bufw);

	fdw = open("21a_fifoFile", O_WRONLY);
    fdr = open("21b_fifoFile", O_RDONLY);
    write(fdw, bufw, sizeof(bufw));
    read(fdr, bufr, sizeof(bufr));
    printf("The text from Pipe2: %s", bufr);
    close(fdw);
    close(fdr);
}