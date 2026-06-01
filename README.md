# Messagerie Console

Une application de messagerie textuelle en C, fonctionnant en ligne de commande (console) via une architecture Client/Serveur. Elle permet à deux utilisateurs de discuter en temps réel sur un réseau local.

## Fonctionnalités

*   **Authentification et Gestion des utilisateurs** : Inscription, connexion, et récupération de mot de passe sécurisée (contraintes de longueur, majuscules, minuscules et caractères spéciaux).
*   **Système unifié** : L'hébergement d'un serveur et la connexion en tant que client se font désormais dans la même interface console.
*   **Auto-détection de l'IP** : Lorsque vous hébergez un serveur, l'application affiche automatiquement votre adresse IP locale pour que vous puissiez la transmettre facilement à votre interlocuteur.
*   **Chat en temps réel** : Discussion asynchrone (multithreading) sans interférence lors de la frappe.
*   **Déconnexion propre** : Possibilité de quitter le chat à tout moment en tapant la commande `/quit`.

## Prérequis

*   **Système d'exploitation** : Windows
*   **Compilateur C** : GCC (MinGW) ou équivalent.
*   **Bibliothèque réseau** : Winsock2 (intégrée à Windows, `ws2_32.lib`).

## Compilation

Ouvrez un terminal dans le répertoire du projet et exécutez la commande suivante :

```bash
gcc main.c messagerie.c menu.c chat.c -lws2_32 -o messagerie_console.exe
```

## Utilisation

1.  **Lancement** : Exécutez le fichier `messagerie_console.exe` généré.
2.  **Création de compte / Connexion** : Créez un compte ou connectez-vous avec vos identifiants.
3.  **Héberger (Serveur)** :
    *   Choisissez l'option *Héberger un serveur de chat*.
    *   L'application affichera votre adresse IP locale. Transmettez-la à l'autre personne.
    *   Attendez que l'autre personne se connecte.
4.  **Rejoindre (Client)** :
    *   Choisissez l'option *Se connecter à un serveur de chat*.
    *   Saisissez l'adresse IP que l'hébergeur vous a fournie.
5.  **Discuter** : Tapez vos messages et appuyez sur *Entrée* pour les envoyer.
6.  **Quitter** : Tapez `/quit` pour revenir au menu principal.
