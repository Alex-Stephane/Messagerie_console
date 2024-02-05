#ifndef MESSAGERIE_H_INCLUDED
#define MESSAGERIE_H_INCLUDED

typedef struct
{
    int jour,mois,annee;
}date;

typedef struct
{
    int id;
    char *nom;
    char *prenom;
    date date_naissance;
    char *username;

}user;
user *new_user;
#endif // MESSAGERIE_H_INCLUDED
