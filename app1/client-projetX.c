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
    char copyReponse[MAXMSG]; // pour stocker le message à envoyer au serveur

	// Test de toutes les fonctions
	testFunctions();

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(false);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */


    envoyer_recevoir("login 11800672 \"BRUN-COSME-GAZOT\"", reponse);

	// Charge l'épreuve
    envoyer_recevoir("load projetX", reponse);
	printf("%s", reponse);

	// Récupère le message crypté, le décrypte et l'affiche
    envoyer_recevoir("help", reponse);
	strcpy(copyReponse, reponse);
	cesarDecodeString(copyReponse);
	printf("%s", copyReponse);

	// Démarre le challenge
    envoyer_recevoir("start", reponse);
	printf("%s", reponse);

	// Envoi le message de validation
    envoyer_recevoir("veni vidi vici", reponse);
	printf("%s", reponse);


    lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(message, reponse); // on envoie message, et on reçoit la réponse du serveur

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}
