#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>


int main()
{
	if(!fork()) {
        printf("Child pid :: %d\n", getpid());
        setsid(); //making session leader or run a program in new session
        //chdir("/");
        umask(0); //permissions 'and with' 0744
        while(1) {
            sleep(6);
            system("bash script30.sh");
        }
    } else exit(0);
    return 0;
}


//kill -9 232584