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
    char buff[8],buff1[12],mes[50];
    printf("\nEnter data:");
    scanf("%s", buff);
    int p[4];
    p[0]=(buff[0]-'0')^(buff[2]-'0')^(buff[3]-'0')^(buff[5]-'0')^(buff[6]-'0');
    p[1]=(buff[0]-'0')^(buff[1]-'0')^(buff[3]-'0')^(buff[4]-'0')^(buff[6]-'0');
    p[2]=(buff[3]-'0')^(buff[4]-'0')^(buff[5]-'0');
    p[3]=(buff[0]-'0')^(buff[1]-'0')^(buff[2]-'0');
    buff1[0] = buff[0];
    buff1[1] = buff[1];
    buff1[2] = buff[2];
    buff1[3] = p[3] + '0';
    buff1[4] = buff[3];
    buff1[5] = buff[4];
    buff1[6] = buff[5];
    buff1[7] = p[2] + '0';
    buff1[8] = buff[6];
    buff1[9] = p[1] + '0';
    buff1[10] =p[0] + '0';
    buff1[11] ='\0';
    printf("\n%s\n",buff1);
    if (send(sockfd, buff1, sizeof(buff1), 0) < 0) {
        printf("send failed");
        exit(1);
    }
    int r = recv(sockfd, mes, sizeof(mes), 0);
    if (r < 0) {
        printf("recv failed");
        exit(1);
    }
    printf("%s\n",mes);
    r = recv(sockfd, buff1, sizeof(buff1), 0);
    if (r < 0) {
        printf("recv failed");
        exit(1);
    }
    printf("\n%s",buff1);
    close(sockfd);
	return 0;
}