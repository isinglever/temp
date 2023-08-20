#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(clientAddr);
    
    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    
    // Bind the socket to an IP and port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding");
        exit(EXIT_FAILURE);
    }
    
    // Listen for connections
    if (listen(serverSocket, 5) == -1) {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }
    
    printf("Server listening on port 8080...\n");
    
    // Accept a connection
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);
    if (clientSocket == -1) {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }
    
    printf("Client connected\n");
    
    char buffer[1024];
    
    while (1) {
        // Receive message from client
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            printf("Connection closed by client\n");
            break;
        }
        
        buffer[bytesRead] = '\0';
        printf("Client: %s", buffer);
        
        // Check if the message is "exit"
        if (strcmp(buffer, "exit\n") == 0) {
            printf("Connection closed by client\n");
            break;
        }
        
        // Send response to client
        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(clientSocket, buffer, strlen(buffer), 0);
    }
    
    // Close sockets
    close(clientSocket);
    close(serverSocket);
    
    return 0;
}
