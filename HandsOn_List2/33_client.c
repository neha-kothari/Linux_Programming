#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h> 

int main(int argc, char *argv[])
{
    struct sockaddr_in server; 
    int socket_desc;
    char buff[1024];
    
    
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htons(43456); 
    
    connect(socket_desc, (struct sockaddr *)&server, sizeof(server));
    write(socket_desc, "Hello server", 13);
    
    read(socket_desc, &buff, sizeof(buff));
    printf("Message from server: %s\n", buff);
    close(socket_desc);
    exit(EXIT_SUCCESS);
}