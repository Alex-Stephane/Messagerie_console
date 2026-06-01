#include "menu.h"
#include "messagerie.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <winsock2.h>


#pragma comment(lib, "ws2_32.lib")

int main() {
  WSADATA wsa;
  User us;

  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
    printf("Erreur d'initialisation de Winsock.\n");
    return 1;
  }

  menu_accueil(&us);

  WSACleanup();
  return 0;
}
