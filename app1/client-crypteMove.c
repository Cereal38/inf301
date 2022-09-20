#include "client.h"
#include "ressources.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP


int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    char message[MAXMSG]; // pour stocker le message à envoyer au serveur
char copyReponse[MAXREP];

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(false);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 443);

// Connexion
    envoyer_recevoir("login 11800672 \"BRUN-COSME-GAZOT\"", reponse);
printf("%s\n", reponse);

// Appel la commande qui charge crypteWave
    envoyer_recevoir("load crypteMove", reponse);
printf("%s\n", reponse);

// Affiche la manière de crypter
    envoyer_recevoir("help", reponse);
printf("%s\n", reponse);

// On récupère la réponse et on la crypte
strcpy(copyReponse, reponse);
encrypteMove(copyReponse);

// Démarre le challenge
envoyer_recevoir("start", reponse);
printf("%s\n", reponse);

// On envoit la réponse
envoyer_recevoir(copyReponse, reponse);
printf("%s\n", reponse);


    lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(message, reponse); // on envoie message, et on reçoit la réponse du serveur

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}


