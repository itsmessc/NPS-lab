#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>

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

    char buff[50];
     int r = recv(ns, buff, sizeof(buff), 0);
    if (r < 0) {
        printf("recv failed");
        exit(1);
    }
    printf("Data received");
    int count=0;
    for(int i=0;buff[i]!='\0';i++){
    	if(buff[i]=='1'){
    		count++;
    	}
    }
    if(count%2==0){
    	strcpy(buff,"Not Corrupted");
    }
    else{
    	strcpy(buff,"Corrupted");
    }
    if (send(ns, buff, sizeof(buff), 0) < 0) {
        printf("send failed");
        exit(1);
    }
    close(ns);
    close(sockfd);
	return 0;
}