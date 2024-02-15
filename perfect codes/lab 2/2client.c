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
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{	printf("socket creation error");
		exit(0);
	}
	int x;
	socklen_t len;

	printf("socket created\n");
	printf("Enter Port number:");
	scanf("%d",&x);
	struct sockaddr_in client;
	client.sin_port = htons(x);
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = inet_addr("127.0.0.1");

	char buff[50];
	len=sizeof(client);
	int sa=sizeof(client),sendd;
	while(1){
		printf("\n Enter message (stop to exit):");
		scanf("%s",buff);
		sendd=sendto(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
		if(sendd==-1){
			close(sockfd);
			printf("\n Failed to send message");
			exit(0);
		}
		if(!strcmp(buff,"stop")){
			break;
		}
	}
	close(sockfd);

}