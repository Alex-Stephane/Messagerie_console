#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "messagerie.h"
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void menu_accueil(User us)
{
    int choix;
    do
    {
        printf("                   --------------------------------------------------\n");
        printf("                                   MESSAGERIE EN LOCAL \n");
        printf("                                   1 : OUVRIR UN COMPTE \n");
        printf("                                   2 : SE CONNECTER \n");
        printf("                                   3 : MOT DE PASSE OUBLIE \n");
        printf("                                   0 : QUITTER \n");
        printf("                   --------------------------------------------------\n");
        printf("Entrer votre choix : ");
        scanf("%d",&choix);
        system("cls");
        switch (choix)
        {
        case 1:
                menu_enregistrer(us);
                system("cls");
            break;

        case 2:
                menu_connecter(us);
                system("cls");
            break;

        case 3:
                menu_forgotpwd(us);
                system("cls");
            break;
        }

    } while (choix != 0);
}

void menu_enregistrer(User us)
{
    system("cls");
    srand(time(NULL)); 
    int choix1;
    printf("    -------------------------------------------------------------------------------------------------------\n  ");
    printf("    -----------------   Bienvenue sur la page d'enregistrement de la messagerie console  ------------------\n  ");
    printf("    -------------------------------------------------------------------------------------------------------\n\n");

    register_user(us);

    printf("1 pour revenir a l'accueil et 2 pour se connecter : ");
    scanf("%d",&choix1);
    if(choix1 == 1){
        system("cls");
        menu_accueil(us);
    }
    else if(choix1 == 2){
        system("cls");
        menu_connecter(us);
    }

}

void menu_connecter(User us) {
    system("cls");
    int choix1;
    printf("    -----------------   Bienvenue sur la page de connexion de la messagerie console      -------------------\n \n ");
    
    printf("\nUsername : ");
    fflush(stdin);
    fgets(us.username, Max_L, stdin);
    us.username[strcspn(us.username, "\n")] = 0;

    printf("Mot de passe : ");
    fgets(us.mdp, Max_L, stdin);
    us.mdp[strcspn(us.mdp, "\n")] = 0;

    auth_user(us);
    /*if (auth_user(us) == 1) {
        printf("Connexion réussie !\n");
        printf("1 : Démarrer un serveur\n");
        printf("2 : Se connecter à un serveur\n");
        printf("Votre choix : ");
        scanf("%d", &choix1);
        getchar();

        if (choix1 == 1) {
            start_server();
        } else if (choix1 == 2) {
            char server_ip[BUFFER_SIZE];
            printf("Entrez l'adresse IP du serveur : ");
            fgets(server_ip, BUFFER_SIZE, stdin);
            server_ip[strcspn(server_ip, "\n")] = 0;
            start_client(server_ip);
        }
    } else {
        printf("Connexion échouée.\n");
    }*/
}

/*void menu_admin(User us)
{
    int choix;
    printf("1: Consulter la liste des utiliateurs\n");
    printf("2: Supprimer un utilisateur\n");
    printf("3: Modifier les membres\n");
    printf("0: Quitter\n");
    printf("Votre choix : ");
    scanf("%d",&choix);

    switch (choix)
    {
    case 1:
        
        break;
    
    default:
        break;
    }
}*/

void menu_forgotpwd(User us)
{
    int choix1;
    system("cls");
    printf("Entrer votre username : ");
    fflush(stdin);
    fgets(us.username,Max_L,stdin);
    us.username[strcspn(us.username, "\n")] = 0;
    forgot_password(us); 
    scanf("%d",&choix1);
    
}
