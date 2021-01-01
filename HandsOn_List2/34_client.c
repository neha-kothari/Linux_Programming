#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
void main()
{
	struct sockaddr_in server;
	int sfd,msgLength;
	char buff[50];
	char result;
	
	
	/*Domain: AF_INET (IPv4 internet protocols)
	  Type: SOCK_STREAM (Sequenced, reliable two way connectionb based byte streams)
	  creating tcp socket, returns socket file descriptor*/
	  
	sfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);  
	
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(43455);  //convers 5555 from host byte order to network byte order
	
	write(1,"Waiting to connect...\n", sizeof("Waiting to connect...\n"));
	connect(sfd,(struct sockaddr *)&server,sizeof(server)); //initiating connection
	
	read(sfd, buff,sizeof(buff));
	printf("%s\n",buff);
	write(1,"Write to server:",sizeof("Write to server"));
	scanf(" %[^\n]",buff);
	write(sfd,buff,sizeof(buff));  //writing message through socket file descriptor

	close(sfd);


}