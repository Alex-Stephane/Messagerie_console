#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "messagerie.h"
#include "menu.h"

const char *File_User = "Users.csv";

void generate_username(char username[], const char *prefix) 
{
    int random_number = rand() % 1000;
    sprintf(username, "%s%d", prefix, random_number);
}

void register_user(User us)
{
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

    printf("\nVotre username est : %s\n", us.username);

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
}

void auth_user(User us)
{
    FILE *f = fopen(File_User, "r");
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), f))
    {
        char file_username[Max_L], file_mdp[Max_L];
        sscanf(line, "%[^;];%[^;]", file_username, file_mdp);

        if (strcmp(us.username, file_username) == 0 && strcmp(us.mdp, file_mdp) == 0)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("Connexion reussie\n");
        
    }
    else
    {
        printf("Connexion echouee\n");
    }
}

void forgot_password(User us)
{
    FILE *f = fopen(File_User, "r+");
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }

    char line[256];
    int found = 0;
    long pos;
    while ((pos = ftell(f)) != -1 && fgets(line, sizeof(line), f))
    {
        char file_mdp[Max_L], file_username[Max_L], file_nom[Max_L], file_prenom[Max_L], file_nais[Max_L];
        sscanf(line, "%[^;];%[^;];%[^;];%[^;];%[^;]", file_username, file_mdp, file_nom, file_prenom, file_nais);

        if (strcmp(us.username, file_username) == 0)
        {
            char mdp[Max_L];
            found = 1;
            printf("Entrer votre nouveau mdp : ");
            fgets(mdp, Max_L, stdin);
            mdp[strcspn(mdp, "\n")] = 0;
            file_nais[strcspn(file_nais, "\n")] = 0;
            fseek(f, pos, SEEK_SET);
            fprintf(f, "%s;%s;%s;%s;%s\n", us.username, mdp, file_nom, file_prenom, file_nais);
            break;
        }
    }
    if (!found)
        printf("Utilisateur introuvable\n");

    fclose(f);
}


