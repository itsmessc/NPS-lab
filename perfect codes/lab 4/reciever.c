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
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024] = {0};

    // Create server socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // Bind socket to port
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 3) == -1) {
        perror("Listen failed");
        return 1;
    }

    printf("Server listening...\n");

    socklen_t client_len = sizeof(client_addr);

    // Accept connection from client
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) == -1) {
        perror("Acceptance failed");
        return 1;
    }

    // Receive data from client
    read(client_socket, buffer, 1024);
    printf("Received data: %s\n", buffer);

    // Receive CRC from client
    unsigned short received_crc;
    read(client_socket, &received_crc, sizeof(received_crc));
    printf("Received CRC: %d\n", received_crc);

    // Calculate CRC for received data
    unsigned short calculated_crc = crc12(buffer, strlen(buffer));
    printf("Calculated CRC: %d\n", calculated_crc);

    // Compare received CRC with calculated CRC
    if (received_crc == calculated_crc) {
        printf("Data integrity verified. No errors.\n");
    } else {
        printf("Data integrity check failed. Errors detected.\n");
    }

    close(server_socket);
    return 0;
}
