#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	// image of this program will be relaced by new program
	execl("neha.out", "neha.c", argv[1],(char *) NULL);
	return 0;
}