#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define POLYNOMIAL 0x80F  // CRC-12 polynomial

unsigned short crc12(char *data, int length) {
    unsigned short crc = 0;
    int i, j;

    for (i = 0; i < length; i++) {
        crc ^= (data[i] << 4);
        for (j = 0; j < 8; j++) {
            if (crc & 0x800) {
                crc ^= (POLYNOMIAL << 1);
            }
            crc <<= 1;
        }
    }

    return (crc >> 4) & 0xFFF;
}

int main() {
    // Create TCP socket
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    // Create client socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8080);

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        return 1;
    }

    // Get data from user
    printf("Enter data to send: ");
    fgets(buffer, 1024, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // remove newline character

    // Calculate CRC for data
    unsigned short calculated_crc = crc12(buffer, strlen(buffer));

    // Send data to server
    send(client_socket, buffer, strlen(buffer), 0);
    printf("Sent data: %s\n", buffer);

    // Send CRC to server
    send(client_socket, &calculated_crc, sizeof(calculated_crc), 0);
    printf("Sent CRC: %d\n", calculated_crc);

    close(client_socket);
    return 0;
}
