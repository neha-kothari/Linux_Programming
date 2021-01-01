#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	// image of this program will be relaced by new program
	int x = execl("neha.out", "neha.c", (char *) NULL);
    printf("x= %d", x);
	return 0;
}