#include "chat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>

#define PORT 8888

// Flag global pour gérer la fermeture propre des threads
volatile int keep_running = 1;

DWORD WINAPI receiveMessages(LPVOID arg) {
  SOCKET sock = *(SOCKET *)arg;
  char buffer[1024];
  int bytes_received;

  while (keep_running &&
         (bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
    buffer[bytes_received] = '\0';
    printf("\r\033[KInterlocuteur: %s\nMessage: ", buffer);
    fflush(stdout);
  }

  if (keep_running) {
    printf("\n\nL'interlocuteur s'est deconnecte. Appuyez sur Entree pour "
           "revenir au menu.\n");
    keep_running = 0;
  }
  return 0;
}

void chat_loop(SOCKET sock) {
  char message[1024];
  HANDLE hThread;

  keep_running = 1;
  hThread = CreateThread(NULL, 0, receiveMessages, &sock, 0, NULL);

  while (keep_running) {
    printf("Message: ");
    if (fgets(message, sizeof(message), stdin) == NULL) {
      break;
    }

    message[strcspn(message, "\n")] = 0;

    if (strcmp(message, "/quit") == 0) {
      keep_running = 0;
      break;
    }

    if (strlen(message) > 0) {
      send(sock, message, strlen(message), 0);
    }
  }

  closesocket(sock);
  keep_running = 0;
  WaitForSingleObject(hThread, 1000);
  CloseHandle(hThread);
  printf("Deconnecte du chat.\n");
}

void start_server() {
  SOCKET server_socket, client_socket;
  struct sockaddr_in server_addr, client_addr;
  int addr_len = sizeof(client_addr);

  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket == INVALID_SOCKET) {
    printf("Erreur de creation du socket.\n");
    return;
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  if (bind(server_socket, (struct sockaddr *)&server_addr,
           sizeof(server_addr)) == SOCKET_ERROR) {
    printf("Erreur de bind.\n");
    closesocket(server_socket);
    return;
  }

  if (listen(server_socket, 1) == SOCKET_ERROR) {
    printf("Erreur de listen.\n");
    closesocket(server_socket);
    return;
  }

  char hostname[256];
  if (gethostname(hostname, sizeof(hostname)) == 0) {
    struct hostent *host_info = gethostbyname(hostname);
    if (host_info != NULL) {
      printf("\n--- Vos adresses IP locales ---\n");
      for (int i = 0; host_info->h_addr_list[i] != 0; i++) {
        struct in_addr addr;
        addr.s_addr = *(u_long *)host_info->h_addr_list[i];
        printf(" -> %s\n", inet_ntoa(addr));
      }
      printf("-----------------------------------------------------------------"
             "---\n\n");
    }
  }

  printf("Serveur en attente de connexion sur le port %d...\n", PORT);
  client_socket =
      accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
  if (client_socket == INVALID_SOCKET) {
    printf("Erreur lors de l'acceptation.\n");
    closesocket(server_socket);
    return;
  }

  printf("Client connecte. Tapez /quit pour quitter.\n");

  chat_loop(client_socket);

  closesocket(server_socket);
}

void start_client(const char *server_ip) {
  SOCKET client_socket;
  struct sockaddr_in server_addr;

  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == INVALID_SOCKET) {
    printf("Erreur de creation du socket.\n");
    return;
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(server_ip);
  if (server_addr.sin_addr.s_addr == INADDR_NONE) {
    printf("Adresse IP invalide.\n");
    closesocket(client_socket);
    return;
  }
  server_addr.sin_port = htons(PORT);

  printf("Connexion au serveur %s...\n", server_ip);
  if (connect(client_socket, (struct sockaddr *)&server_addr,
              sizeof(server_addr)) != 0) {
    printf("Connexion echouee.\n");
    closesocket(client_socket);
    return;
  }

  printf("Connecte au serveur. Tapez /quit pour quitter.\n");

  chat_loop(client_socket);
}
