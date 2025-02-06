#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "messagerie.h"

const char *File_User = "Users.csv";

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

void menu_enregistrer(User us)
{
    int choix1;
    printf("    -------------------------------------------------------------------------------------------------------\n  ");
    printf("    -                                                                                                     -\n  ");
    printf("    -                                                                                                     -\n  ");
    printf("    -----------------   Bienvenue sur la page d'enregistrement de la messagerie console  ------------------\n  ");
    printf("    -                                                                                                     -\n  ");
    printf("    -                                                                                                     -\n  ");
    printf("    -------------------------------------------------------------------------------------------------------\n\n  ");

    printf("Entrer votre nom\n");
    fgets(us.nom,Max_L,stdin);
    printf("Entrer votre prenom\n");
    fgets(us.prenom,Max_L,stdin);
    printf("Entrer votre date de naissance\n");
    scanf("%d %d %d",&us.date_nais.jour,&us.date_nais.mois,&us.date_nais.annee);
    printf("Nom : %s\n Prenom: %s\n Date de naissance : %d/%d/%d\n",us.nom,us.prenom,us.date_nais.jour,us.date_nais.mois,us.date_nais.annee);
    
    FILE *f = fopen(File_User,"a+");
    if( f == NULL)
    {
        printf("erreur lors de l'ouverture du fichier\n");
        return;
    }
    else
    {
        fprintf(File_User,"%s,%s,%d|%d|%d\n",j.nom,j.prenom,j.dateNais.jour,j.dateNais.mois,j.dateNais.annee);
        printf("\n");
        printf("enregistrement d'un nouvel utilisateur !\n");
        printf("\n");
        fclose(File_User);
    }
    
    printf("1 pour revenir a l'accueil et 2 pour se connecter\n");
    scanf("%d",&choix1);
    if(choix1 == 1)
        menu_accueil();
    else if(choix1 == 2){
        menu_connecter();}

    system("cls");
}

void menu_connecter(User us)
{
    printf("    -----------------   Bienvenue sur la page de connexion de la messagere console      -------------------\n \n ");
    printf("            Entrer votre identifiant\n");
    fgets(us.nom,Max_L,stdin);   
    printf("            Entrer votre mot de passe\n");
    fgets(us.prenom,Max_L,stdin);

}
