// serveur_chat.c
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8888

SOCKET client_socket;

DWORD WINAPI receiveMessages(LPVOID arg) {
    char buffer[1024];
    int bytes_received;

    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("\nClient: %s\nMessage: ", buffer);
        fflush(stdout);
    }

    return 0;
}

int main() {
    WSADATA wsa;
    SOCKET server_socket;
    struct sockaddr_in server_addr, client_addr;
    int addr_len = sizeof(client_addr);
    char message[1024];

    WSAStartup(MAKEWORD(2, 2), &wsa);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 1);

    printf("En attente de connexion...\n");
    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
    printf("Client connecté.\n");

    // Créer un thread pour recevoir les messages
    CreateThread(NULL, 0, receiveMessages, NULL, 0, NULL);

    // Boucle d'envoi
    while (1) {
        printf("Message: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}
