#ifndef MESSAGERIE_H_INCLUDED
#define MESSAGERIE_H_INCLUDED
#define Max_L 50

typedef struct
{
    int jour,mois,annee;
}date;

typedef struct
{
    int id;
    char nom[Max_L];
    char prenom[Max_L];
    date date_nais;
    char username[Max_L];

}User;

void menu_accueil();
void menu_connecter();
void menu_enregistrer();

#endif // MESSAGERIE_H_INCLUDED
