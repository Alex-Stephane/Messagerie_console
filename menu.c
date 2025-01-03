#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "messagerie.h"
#include "menu.h"
#include "auth.h"

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
        printf("                   --------------------------------------------------\n");
        scanf("%d",&choix);
        system("cls");
        switch (choix)
        {
        case 1:
                menu_enregistrer();
                system("cls");

            break;

        case 2:
                menu_connecter();
                system("cls");

            break;
        }

    } while (choix != 0);
}

void menu_enregistrer()
{
    int choix1;
    printf("    -------------------------------------------------------------------------------------------------------\n  ");
    printf("    -                                                                                                     -\n  ");
    printf("    -                                                                                                     -\n  ");
    printf("    -----------------   Bienvenue sur la page d'enregistrement de la messagerie console  ------------------\n  ");
    printf("    -                                                                                                     -\n  ");
    printf("    -                                                                                                     -\n  ");
    printf("    -------------------------------------------------------------------------------------------------------\n\n  ");

    user *new_user;
    printf("Entrer votre nom\n");
    scanf("%[^\n]s",new_user->nom);
    //gets(new_user->nom);
    printf("Entrer votre prenom\n");
    gets(new_user->prenom);
    printf("Entrer votre prenom\n");
    gets(new_user->prenom);

    printf("1 pour revenir a l'accueil et 2 pour se connecter\n");
    scanf("%d",&choix1);
    if(choix1 == 1)
        menu_accueil();
    else if(choix1 == 2){
        menu_connecter();}
    system("cls");
}

void menu_connecter()
{
    printf("    -----------------   Bienvenue sur la page de connexion de la messagere console      -------------------\n \n ");
    printf("            Entrer votre identifiant\n");
    //gets();
    printf("            Entrer votre mot de passe\n");
    //gets();


}
