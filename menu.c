#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "messagerie.h"
#include <time.h>

const char *File_User = "Users.csv";

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
        }

    } while (choix != 0);
}

void menu_enregistrer(User us)
{
    srand(time(NULL)); 
    int choix1;
    printf("    -------------------------------------------------------------------------------------------------------\n  ");
    printf("    -                                                                                                     -\n  ");
    printf("    -                                                                                                     -\n  ");
    printf("    -----------------   Bienvenue sur la page d'enregistrement de la messagerie console  ------------------\n  ");
    printf("    -                                                                                                     -\n  ");
    printf("    -                                                                                                     -\n  ");
    printf("    -------------------------------------------------------------------------------------------------------\n\n  ");

    printf("Entrer votre nom : ");
    fflush(stdin);
    fgets(us.nom, Max_L, stdin);
    us.nom[strcspn(us.nom, "\n")] = 0; 

    printf("Entrer votre prenom : ");
    fgets(us.prenom, Max_L, stdin);
    us.prenom[strcspn(us.prenom, "\n")] = 0;

    char mdp1[Max_L], mdp2[Max_L];
    do
    {
        printf("Entrer votre mot de passe : ");
        fgets(mdp1, Max_L, stdin);
        printf("Confirmer votre mot de passe : ");
        fgets(mdp2, Max_L, stdin);
        if(strcmp(mdp1,mdp2) != 0)
            printf("Mot de passe incorrect\n Recommencez\n");
    } while (strcmp(mdp1,mdp2) != 0);
    strcpy(us.mdp, mdp1);
    us.mdp[strcspn(us.mdp, "\n")] = 0;

    printf("Entrer votre date de naissance (jj mm aaaa): ");
    scanf("%d %d %d", &us.date_nais.jour, &us.date_nais.mois, &us.date_nais.annee);
    generate_username(us.username, "user");

    printf("Username : %s\nMot de passe : %s\nNom : %s\nPrenom: %s\nDate de naissance : %d/%d/%d\n", us.username, us.mdp, us.nom, us.prenom, us.date_nais.jour, us.date_nais.mois, us.date_nais.annee);

    FILE *f = fopen(File_User, "a+");
    if (f == NULL)
    {
        printf("erreur lors de l'ouverture du fichier\n");
    }
    else
    {
        fprintf(f, "\n%s;%s;%s;%s;%d/%d/%d", us.username, us.mdp, us.nom, us.prenom, us.date_nais.jour, us.date_nais.mois, us.date_nais.annee);
        printf("\n");
        printf("enregistrement d'un nouvel utilisateur effectué !\n");
        printf("\n");
        fclose(f);
    }

    printf("1 pour revenir a l'accueil et 2 pour se connecter : ");
    scanf("%d",&choix1);
    if(choix1 == 1)
        menu_accueil(us);
    else if(choix1 == 2){
        menu_connecter(us);}
    system("cls");
}

void menu_connecter(User us)
{
    printf("    -----------------   Bienvenue sur la page de connexion de la messagere console      -------------------\n \n ");
    printf("Username : ");
    fgets(us.username,Max_L,stdin);   
    printf("Mot de passe : ");
    fgets(us.prenom,Max_L,stdin);

}
