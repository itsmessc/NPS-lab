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
  	printf("\nSocket listening.\n");
  	len = sizeof(client);
  	int ns = accept(sockfd, (struct sockaddr * ) & client, & len);
  	if(ns==-1){
  		close(sockfd);
  		exit(0);
  	}
  	printf("\nsocket is ready to accept\n");
  	char buff[50];
  	rece=recv(ns,buff,sizeof(buff),0);
  	if(rece==-1){
  		printf("Receiving failed");
  	}
  	int i=0,j=0,m=0;
  	char num[50],al[50];
  	for(m=0;buff[m]!='\0';m++){
  		if((buff[m] >= 65 && buff[m] <= 91) || (buff[m] >= 97 && buff[m] <= 123)){
  			al[i++]=buff[m];
  		}
  		if(buff[m]>='0'&&buff[m]<='9'){
  			num[j++]=buff[m];
  		}
  	}
  	al[i]='\0';
  	num[j]='\0';
  	int pid=fork();
  	if(pid>0){
  		for(m=0;m<i-1;m++){
  			for(int x=0;x<i-m-1;x++){
  				if(al[x]<al[x+1]){
  					char op=al[x];
  					al[x]=al[x+1];
  					al[x+1]=op;
  				}
  			}
  		}
  		sendd=send(ns,al,sizeof(al),0);
  	}
  	else{
  		for(m=0;m<j-1;m++){
  			for(int x=0;x<j-m-1;x++){
  				if(num[x]>num[x+1]){
  					char op=num[x];
  					num[x]=num[x+1];
  					num[x+1]=op;
  				}
  			}
  		}
  		sendd=send(ns,num,sizeof(num),0);
  	}
  	close(ns);
  	close(sockfd);
}
