// client_chat.c
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "192.168.1.139"  // <-- Remplace par l'IP du serveur
#define PORT 8888

SOCKET client_socket;

DWORD WINAPI receiveMessages(LPVOID arg) {
    char buffer[1024];
    int bytes_received;

    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("\nServeur: %s\nMessage: ", buffer);
        fflush(stdout);
    }

    return 0;
}

int main() {
    WSADATA wsa;
    struct sockaddr_in server_addr;
    char message[1024];

    WSAStartup(MAKEWORD(2, 2), &wsa);

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
        printf("Connexion échouée.\n");
        return 1;
    }

    printf("Connecté au serveur.\n");

    // Créer un thread pour recevoir les messages
    CreateThread(NULL, 0, receiveMessages, NULL, 0, NULL);

    // Boucle d'envoi
    while (1) {
        printf("Message: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);
    }

    closesocket(client_socket);
    WSACleanup();
    return 0;
}
