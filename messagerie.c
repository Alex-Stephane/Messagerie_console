#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>  
#include <ctype.h>
#include "messagerie.h"
#include "menu.h"

const char *File_User = "Users.csv";
const char *File_admin = "Admin.csv";

void generate_username(char username[], const char *prefix) 
{
    int random_number = rand() % 1000;
    sprintf(username, "%s%d", prefix, random_number);
}

int check_password_strength(const char *mdp)
{
    int len = strlen(mdp);
    if (len < 8 || len > 20) return 0;

    int has_upper = 0;
    int has_lower = 0;
    int has_special = 0;

    for (int i = 0; i < len; i++) {
        if (isupper(mdp[i])) has_upper = 1;
        else if (islower(mdp[i])) has_lower = 1;
        else if (!isalnum(mdp[i]) && !isspace(mdp[i])) has_special = 1;
    }

    return has_upper && has_lower && has_special;
}

void register_user(User *us)
{
    printf("Entrer votre nom : ");
    fflush(stdin);
    fgets(us->nom, Max_L, stdin);
    us->nom[strcspn(us->nom, "\n")] = 0; 

    printf("Entrer votre prenom : ");
    fgets(us->prenom, Max_L, stdin);
    us->prenom[strcspn(us->prenom, "\n")] = 0;

    char mdp1[Max_L], mdp2[Max_L];
    int valid_pwd = 0;
    do
    {
        printf("Entrer votre mot de passe (8-20 car., min 1 maj, 1 min, 1 spec) : ");
        fgets(mdp1, Max_L, stdin);
        mdp1[strcspn(mdp1, "\n")] = 0;
        
        printf("Confirmer votre mot de passe : ");
        fgets(mdp2, Max_L, stdin);
        mdp2[strcspn(mdp2, "\n")] = 0;

        if (strcmp(mdp1, mdp2) != 0) {
            printf("Les mots de passe ne correspondent pas.\n");
        } else if (!check_password_strength(mdp1)) {
            printf("Le mot de passe ne respecte pas les criteres de securite.\n");
        } else {
            valid_pwd = 1;
        }
    } while (!valid_pwd);
    
    strcpy(us->mdp, mdp1);

    printf("Entrer votre date de naissance (jj mm aaaa): ");
    scanf("%d %d %d", &us->date_nais.jour, &us->date_nais.mois, &us->date_nais.annee);
    generate_username(us->username, "user");

    printf("\nVotre username est : %s\n", us->username);

    FILE *f = fopen(File_User, "a+");
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
    }
    else
    {
        fprintf(f, "%s;%s;%s;%s;%d/%d/%d\n", us->username, us->mdp, us->nom, us->prenom, us->date_nais.jour, us->date_nais.mois, us->date_nais.annee);
        printf("\n");
        printf("Enregistrement d'un nouvel utilisateur effectue !\n");
        printf("\n");
        fclose(f);
    }
}

int auth_user(User *us)
{
    FILE *f = fopen(File_User, "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return 0;
    }
    

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), f))
    {
        char file_username[Max_L], file_mdp[Max_L];
        sscanf(line, "%[^;];%[^;]", file_username, file_mdp);

        if (strcmp(us->username, file_username) == 0 && strcmp(us->mdp, file_mdp) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(f);
    return found;
}

void forgot_password(User *us)
{
    FILE *f = fopen(File_User, "r");
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }

    FILE *f_temp = fopen("temp.csv", "w");
    if (f_temp == NULL) {
        printf("Erreur lors de la creation du fichier temporaire\n");
        fclose(f);
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), f))
    {
        char file_mdp[Max_L], file_username[Max_L], file_nom[Max_L], file_prenom[Max_L], file_nais[Max_L];
        sscanf(line, "%[^;];%[^;];%[^;];%[^;];%[^\n]", file_username, file_mdp, file_nom, file_prenom, file_nais);

        if (strcmp(us->username, file_username) == 0)
        {
            char mdp1[Max_L], mdp2[Max_L];
            int valid_pwd = 0;
            found = 1;
            do {
                printf("Entrer votre nouveau mot de passe (8-20 car., min 1 maj, 1 min, 1 spec) : ");
                fgets(mdp1, Max_L, stdin);
                mdp1[strcspn(mdp1, "\n")] = 0;

                printf("Confirmer votre mot de passe : ");
                fgets(mdp2, Max_L, stdin);
                mdp2[strcspn(mdp2, "\n")] = 0;

                if (strcmp(mdp1, mdp2) != 0) {
                    printf("Les mots de passe ne correspondent pas.\n");
                } else if (!check_password_strength(mdp1)) {
                    printf("Le mot de passe ne respecte pas les criteres de securite.\n");
                } else {
                    valid_pwd = 1;
                }
            } while (!valid_pwd);

            fprintf(f_temp, "%s;%s;%s;%s;%s\n", us->username, mdp1, file_nom, file_prenom, file_nais);
        }
        else
        {
            fprintf(f_temp, "%s", line);
        }
    }

    fclose(f);
    fclose(f_temp);

    if (found) {
        remove(File_User);
        rename("temp.csv", File_User);
        printf("Mot de passe modifie avec succes.\n");
    } else {
        remove("temp.csv");
        printf("Utilisateur introuvable.\n");
    }
}
