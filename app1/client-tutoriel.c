#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    char message[MAXMSG]; // pour stocker le message à envoyer au serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */


	// Login
    envoyer_recevoir("login 11800672 \"BRUN-COSME-GAZOT\"", reponse);

	// Lance l'épreuve
    envoyer_recevoir("load tutoriel", reponse);
    envoyer_recevoir("aide", reponse);
    envoyer_recevoir("start", reponse);

	// Envoi les réponses
    envoyer_recevoir("oui", reponse);
    envoyer_recevoir("4", reponse);
    envoyer_recevoir("blanc", reponse);
    envoyer_recevoir("Pincemoi", reponse);
    envoyer_recevoir("tutoriel", reponse);


    lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(message, reponse); // on envoie message, et on reçoit la réponse du serveur

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}
