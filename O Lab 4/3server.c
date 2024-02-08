#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include<math.h>
int main(int argc, char const *argv[])
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr, c_addr;
    socklen_t len;

    if (sockfd < 0) {
        printf("socket creation error\n");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1342);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding error");
        exit(1);
    }
    printf("Binding Successful\n");

    listen(sockfd, 1);
    printf("The server is ready for listening.\n");
    len = sizeof(c_addr);
    int ns = accept(sockfd, (struct sockaddr*)&c_addr, &len);

    char buff[50],buff1[50];
     int r = recv(ns, buff, sizeof(buff), 0);
    if (r < 0) {
        printf("recv failed");
        exit(1);
    }
    printf("Data received\n");
    printf("\n%s\n",buff);
    int p[4];
    p[3]=(buff[0]-'0')^(buff[2]-'0')^(buff[4]-'0')^(buff[6]-'0')^(buff[8]-'0')^(buff[10]-'0');
    p[2]=(buff[0]-'0')^(buff[1]-'0')^(buff[4]-'0')^(buff[5]-'0')^(buff[8]-'0')^(buff[9]-'0');
    p[1]=(buff[6]-'0')^(buff[4]-'0')^(buff[5]-'0')^(buff[7]-'0');
    p[0]=(buff[0]-'0')^(buff[1]-'0')^(buff[2]-'0')^(buff[3]-'0');
   
    printf("\n%d %d %d %d",p[0],p[1],p[2],p[3]);
    int flag=0;
    for(int i=0;i<4;i++){
    	if(p[i]!=0){
    		strcpy(buff1,"Corrupted");
    		flag=1;
    		break;
    	}
    }
    if(flag==0){
    	strcpy(buff1,"Not Corrupted");
    }
    if (send(ns, buff1, sizeof(buff), 0) < 0) {
        printf("send failed");
        exit(1);
    }
    if(flag==1){
    	int l=(p[3]*pow(2,3))+(p[2]*pow(2,2))+(p[1]*pow(2,1))+(p[0]*pow(2,0));
    	buff[l-1]=((buff[0]-'0')^1)+'0';
    	printf("\n%s\n",buff);
    }
    if (send(ns, buff, sizeof(buff), 0) < 0) {
        printf("send failed");
        exit(1);
    }
	return 0;
}