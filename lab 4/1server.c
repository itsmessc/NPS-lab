#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>

int main() {
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
    char buff[50], buff1[50];
    int r = recv(ns, buff, sizeof(buff), 0);
    if (r < 0) {
        printf("recv failed");
        exit(1);
    }
    printf("\nFile Name Received!\n");
    FILE* f;
    strcat(buff, ".txt");
    if ((f = fopen(buff, "r")) != NULL) {
        strcpy(buff1, buff);
        strcpy(buff, "File Exist");
    }
    else {
        strcpy(buff, "File does not exist");
    }

    if (send(ns, buff, sizeof(buff), 0) == -1) {
        printf("\nMessage Sending Failed");
        close(sockfd);
        close(ns);
        exit(1);
    }
    if (strcmp(buff, "File does not exist") == 0) {
        close(sockfd);
        close(ns);
        exit(1);
    }

    while (1) {
        int option;
        if (recv(ns, &option, sizeof(option), 0) < 0) {
            printf("Option receive failed");
            exit(1);
        }

        if (option == 1) {
            char searchWord[50];
            if (recv(ns, searchWord, sizeof(searchWord), 0) < 0) {
                printf("Search word receive failed");
                exit(1);
            }

            int count = 0;
            char word[100];
            while (fscanf(f, "%s", word) != EOF) {
                if (strcmp(word, searchWord) == 0) {
                    count++;
                }
            }

            if (send(ns, &count, sizeof(count), 0) == -1) {
                printf("Count sending failed");
                exit(1);
            }
        } else if (option == 4) {
            break; // Exit the loop and close the connection
        }
    }

    close(ns);
    close(sockfd);
    return 0;
}
