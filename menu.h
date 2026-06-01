#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

typedef struct User User;

void menu_accueil(User *us);
void menu_enregistrer(User *us);
void menu_connecter(User *us);
// void menu_admin(User *us);
void menu_forgotpwd(User *us);

#endif // MENU_H_INCLUDED
