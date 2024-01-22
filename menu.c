#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "messagerie.h"
#include "menu.h"

void menu_accueil()
{
    int choix;
do
    {
        printf("                   --------------------------------------------------\n");
        printf("                                   MESSAGERIE EN LOCAL \n");
        printf("                                   1 : OUVRIR UN COMPTE \n");
        printf("                                   2 : SE CONNECTER \n");
        printf("                                   0 : QUITTER \n");
        printf("                   --------------------------------------------------");
        scanf("%d",&choix);
        system("cls");
        switch (choix)
        {
        case 1:
                printf(" OUVRIR UN COMPTE \n");
            break;

        case 2:
                printf(" Se connecter \n");
            break;
        }

    } while (choix != 0);
}
