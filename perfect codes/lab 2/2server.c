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

void swap(char * x, char * y) 
{
  char temp;
  temp = * x;
  * x = * y;
  * y = temp;
}
void permute(char * a, int l, int r) 
{
  int i;
  if (l == r)
    printf("%s\n", a);
  else 
  {
    for (i = l; i <= r; i++) 
    {
      swap((a + l), (a + i));
      permute(a, l + 1, r);
      swap((a + l), (a + i)); 
    }
  }
}

int main(){
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1)
	{	printf("socket creation error\n");
		exit(0);
	}
	struct sockaddr_in server, client;
	server.sin_family = AF_INET;
  	server.sin_port = htons(3388);
  	server.sin_addr.s_addr = htonl(INADDR_ANY);
  	socklen_t len;
  	int ca = sizeof(client);
  	int r,sendd,rece;

  	r=bind(sockfd, (struct sockaddr * ) & server, sizeof(server));
  	if(r==-1){
  		printf("Binding error");
  		exit(0);
  	}
  	printf("Binding successful\n");
  	char buff[50];
  	while(1){
  		rece=recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
  		if(rece==-1){
  			printf("Failed to receive");
  			close(sockfd);
  			exit(0);
  		}
  		printf("Message received\n Message:%s\n",buff);
  		if(!strcmp(buff,"stop")){
  			close(sockfd);
  			exit(0);
  		}
  		printf("\nPermutations of the string are: \n");
    	int n = strlen(buff);
    	permute(buff, 0, n - 1);
  	}
  	close(sockfd);
}