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
    if (sockfd == -1) {
        printf("socket creation error");
        exit(1);
    }

    struct sockaddr_in c_addr;
    c_addr.sin_port = htons(1342);
    c_addr.sin_family = AF_INET;
    c_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int size = sizeof(struct sockaddr);
    if(connect(sockfd, (struct sockaddr*) &c_addr, sizeof(c_addr))>=0){
    	printf("\nConnection successful");
    }
    char buff[50];
    printf("Enter data");
    scanf("%s", buff);
    if (send(sockfd, buff, sizeof(buff), 0) < 0) {
        printf("send failed");
        exit(1);
    }
    int r = recv(sockfd, buff, sizeof(buff), 0);
    if (r < 0) {
        printf("recv failed");
        exit(1);
    }
    printf("%s",buff);
    close(sockfd);
	return 0;
}