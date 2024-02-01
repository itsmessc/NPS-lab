#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main() {
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
    connect(sockfd, (struct sockaddr*) &c_addr, sizeof(c_addr));

    char buff[50];
    printf("Enter file name:");
    scanf("%s", buff);
    if (send(sockfd, buff, sizeof(buff), 0) < 0) {
        printf("send failed");
        exit(1);
    }
    recv(sockfd, buff, sizeof(buff), 0);
    printf("%s\n", buff);

    int n, count, m;
    while (1) {
        printf("1.Search\n2.Replace\n3.Rearrange\n4.Exit\n");
        printf("Enter input:");
        scanf("%d", &n);
        switch (n) {
            case 1:
                printf("Enter word to search:");
                scanf("%s", buff);
                m = 1;
                if (send(sockfd, &m, sizeof(m), 0) < 0) {
                    printf("send failed");
                    exit(1);
                }
                if (send(sockfd, buff, sizeof(buff), 0) < 0) {
                    printf("send failed");
                    exit(1);
                }
                if (recv(sockfd, &count, sizeof(count), 0) < 0) {
                    perror("Receiving failed");
                    exit(1);
                }
                printf("Repeated %d times\n", count);
                break;
            case 4:
                // Add code to send the exit option to the server and then close the connection
                // ...
                close(sockfd);
                exit(0);
        }
    }

    close(sockfd);
    return 0;
}
