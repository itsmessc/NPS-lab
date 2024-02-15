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
	c_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int r=connect(sockfd, (struct sockaddr*) &c_addr,sizeof(c_addr)),rece,sendd;
	if(r==-1){
		printf("\nconnection error");
		exit(0);
	}
	char buff[50];
	printf("\nSocket connected.\n");
	printf("Enter String");
	scanf("%s",buff);
	sendd=send(sockfd, buff, sizeof(buff), 0);
	if(sendd==-1){
		printf("Message sending failed\n");
		close(sockfd);
	}
	rece=recv(sockfd,buff,sizeof(buff),0);
	if(rece==-1){
		printf("Receiving failed\n");
		close(sockfd);
	}
	printf("%s\n",buff);
	rece=recv(sockfd,buff,sizeof(buff),0);
	if(rece==-1){
		printf("Receiving failed\n");
		close(sockfd);
	}
	printf("%s\n",buff);
	close(sockfd);
}