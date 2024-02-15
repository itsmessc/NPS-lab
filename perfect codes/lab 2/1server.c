#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

int main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	socklen_t len;

	if(sockfd == -1)
	{	printf("socket creation error");
		exit(0);
	}
	printf("Socket created");
	struct sockaddr_in server, client;
	server.sin_family = AF_INET;
	server.sin_port = htons(3388);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	int r = bind(sockfd, (struct sockaddr * ) & server, sizeof(server));

	char buff[20],buff1[20];

	int sendd,rece;
	if (r == -1) 
  	{
    	printf("\nBinding error.");
    	exit(0);
  	}
  	printf("\nSocket binded.");
 	r = listen(sockfd, 1);
  	if (r == -1) 
  	{
    	close(sockfd);
    	exit(0);
  	}
  	printf("\nSocket listening.");
  	len = sizeof(client);
  	int ns = accept(sockfd, (struct sockaddr * ) & client, & len);
  	if(ns==-1){
  		close(sockfd);
  		exit(0);
  	}
  	printf("socket is ready to accept");
  	int pid;
  	printf( "Main Process, PID : %d && PPID : %d\n" ,getpid() , getppid( )) ;
  	pid = fork();
  	while(1){
  		if(pid>0){
  			printf( "\nParent process PID : %d && PPID : %d\n" ,getpid() , getppid()) ;
  			printf("\nParent:");
  			scanf("%s",buff1);
  			sendd=send(ns,buff1,sizeof(buff),0);
  			if(sendd==-1){
  				printf("\n Failed to send");
  				close(sockfd);
  				close(ns);
  				exit(0);
  			}
  			if (strcmp(buff1, "BYE") == 0)
        	break;
  		}
  		else{
  			printf( "\n Child process PID : %d && PPID : %d\n" ,getpid() , getppid()) ;
  			rece=recv(ns,buff,sizeof(buff),0);
  			if(rece==-1){
  				printf("\n Failed to receive");
  				close(sockfd);
  				close(ns);
  				exit(0);
  			}
  			if (strcmp(buff, "BYE") == 0)
        	break;
  			printf("\nChild: %s\n",buff);
  		}
  	}
  	close(ns);
  	close(sockfd);
}