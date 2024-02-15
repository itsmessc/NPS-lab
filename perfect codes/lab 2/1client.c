#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>


int main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{	printf("socket creation error");
		exit(0);
	}
	struct sockaddr_in c_addr;
	c_addr.sin_port = htons(3388);
	c_addr.sin_family = AF_INET;
	c_addr.sin_addr.s_addr = inet_addr("172.16.53.66");
	int r=connect(sockfd, (struct sockaddr*) &c_addr,sizeof(c_addr)),rece,sendd;
	if(r==-1){
		printf("\nconnection error");
		exit(0);
	}
	printf("\nSocket connected.\n");
	int pid;
  	printf( "PID : %d && PPID : %d\n" ,getpid() , getppid()) ;
  	pid = fork();
  	char buff[20],buff1[20];

  	while(1){
  		if(pid>0){
  			printf( " \nParent process PID : %d && PPID : %d\n" ,getpid() , getppid()) ;
  			rece=recv(sockfd,buff,sizeof(buff),0);
  			if(rece==-1){
  				printf("\n Failed to receive");
  				close(sockfd);
  				exit(0);
  			}
  			if (strcmp(buff, "BYE") == 0)
        	break;
  			printf("\nParent: %s\n",buff);
  		}
  		else{
  			printf( "\nChild process PID : %d && PPID : %d\n" ,getpid() , getppid()) ;
  			printf("\nChild:");
  			scanf("%s",buff1);
  			sendd=send(sockfd,buff1,sizeof(buff),0);
  			if(sendd==-1){
  				printf("\n Failed to send");
  				close(sockfd);
  				exit(0);
  			}
  			if (strcmp(buff1, "BYE") == 0)
        	break;
  		}
  	}
  	close(sockfd);
}
