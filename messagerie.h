#ifndef MESSAGERIE_H_INCLUDED
#define MESSAGERIE_H_INCLUDED
#include "menu.h"
#define Max_L 50

typedef struct
{
    int jour,mois,annee;
}Date;

typedef struct
{
    int id;
    char nom[Max_L];
    char prenom[Max_L];
    Date date_nais;
    char username[Max_L];
    char mdp[Max_L];
}User;

void generate_username(char username[], const char *prefix);
void register_user(User us);
void auth_user(User us);
void forgot_password(User us);
void menu_forgotpwd(User us);
void menu_accueil(User us);
void menu_connecter(User us);
void menu_enregistrer(User us);

#endif // MESSAGERIE_H_INCLUDED
