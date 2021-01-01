#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
void *connection_handler(void *nsd)
{
	int nsfd=*(int*)nsd;
	char buff[50];
	write(1,"Connected to client...\n",sizeof("Connected to client...\n"));
	write(nsfd,"Connected to server...\n",sizeof("Connected to server...\n"));
	read(nsfd, buff,sizeof(buff));
	printf("%s\n",buff);

}
int main()
{
	struct sockaddr_in serverad,clientad;
	int sfd,nsd,clientLen;
	pthread_t threads;
	char buff[50];
	
	
	/*Domain: AF_INET (IPv4 internet protocols)
	  Type: SOCK_STREAM (Sequenced, reliable two way connectionb based byte streams)
	  creating tcp socket, returns socket file descriptor*/
	  
	sfd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);  
	
	serverad.sin_family=AF_INET;
	serverad.sin_addr.s_addr=INADDR_ANY;
	serverad.sin_port=htons(43455);  						//convers 5555 from host byte order to network byte order
	
	bind(sfd,(struct sockaddr *)&serverad,sizeof(serverad));    //binds a name to socket
	
	listen(sfd,5); 									//coverts socket to passive, used to accept connections

	printf("Waiting for client...\n");
	while(1)
	{
		clientLen=sizeof(clientad);
		nsd=accept(sfd,(struct sockaddr *)&clientad,&clientLen);  //accepting connection
		if(pthread_create(&threads,NULL,connection_handler,(void*)&nsd)<0)
		{
			perror("Error");
			return 1;
		}
		
	}
	pthread_exit(NULL);
	close(sfd);
	return 0;
}