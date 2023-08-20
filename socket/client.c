#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    
    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    
    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use the server's IP
    
    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting");
        exit(EXIT_FAILURE);
    }
    
    printf("Connected to server\n");
    
    char message[1024];
    
    while (1) {
        printf("Client: ");
        fgets(message, sizeof(message), stdin);
        
        // Send message to server
        send(clientSocket, message, strlen(message), 0);
        
        // Check if the message is "exit"
        if (strcmp(message, "exit\n") == 0) {
            printf("Connection closed by client\n");
            break;
        }
        
        // Receive response from server
        int bytesRead = recv(clientSocket, message, sizeof(message), 0);
        if (bytesRead <= 0) {
            printf("Connection closed by server\n");
            break;
        }
        
        message[bytesRead] = '\0';
        printf("Server: %s", message);
    }
    
    // Close socket
    close(clientSocket);
    
    return 0;
}
