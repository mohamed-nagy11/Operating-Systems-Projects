#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX 80
#define SERVER_PORT 7777
#define SA struct sockaddr

int main() {
    int custom_client_socket;
    struct sockaddr_in custom_servaddr;
    char server_ip[] = "127.0.0.1"; // Server IP address

    // Socket create and verification
    custom_client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (custom_client_socket == -1) {
        perror("Socket creation failed...");
        exit(0);
    } else
        printf("Socket successfully created..\n");
    bzero(&custom_servaddr, sizeof(custom_servaddr));

    // Assign IP, PORT
    custom_servaddr.sin_family = AF_INET;
    custom_servaddr.sin_addr.s_addr = inet_addr(server_ip);
    custom_servaddr.sin_port = htons(SERVER_PORT);

    // Connect the client socket to the server socket
    if (connect(custom_client_socket, (SA*)&custom_servaddr, sizeof(custom_servaddr)) != 0) {
        perror("Connection with the server failed...");
        exit(0);
    } else
        printf("Connected to the custom server at %s:%d successfully\n", server_ip, SERVER_PORT);

    // Function for remote shell command execution
    while (1) {
        char command[MAX];
        printf("Enter the shell command (or 'quit' to exit): ");
        fgets(command, MAX, stdin);

        if (strcmp(command, "quit\n") == 0) {
            // Exit the client if 'quit' command is entered
            close(custom_client_socket);
            printf("Client Exit...\n");
            break;
        }

        write(custom_client_socket, command, strlen(command));
        char buffer[MAX];
        bzero(buffer, MAX);
        read(custom_client_socket, buffer, sizeof(buffer));
        printf("From Custom Server: %s", buffer);
    }
    return 0;
}
