#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{

	int socket_fd, conn_fd, size_client;
	struct sockaddr_in server, client;
	char buff[1024];
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);	
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(43456);

	bind(socket_fd, (struct sockaddr*)&server, sizeof(server));
	
	listen(socket_fd, 1);
    size_client=sizeof(client);	
	conn_fd = accept(socket_fd, (void*)(&client), &size_client);
	read(conn_fd, buff, sizeof(buff));
	printf("Message from client: %s\n", buff);
	write(conn_fd, "ACK from server", 16);
	close(socket_fd);
}