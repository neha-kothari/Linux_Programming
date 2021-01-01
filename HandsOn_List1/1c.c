#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>    
#include <stdlib.h>    
#include <unistd.h>


int main() {
   
    char path_name[] = "./sample_1c";
    int fifo_pipe = mkfifo(path_name, 0644);
    return 0;
}