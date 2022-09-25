#include "client.h"
#include "ressources.h"
#include "asserts.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    char message[MAXMSG]; // pour stocker le message à envoyer au serveur
	char password[MAXMSG];

	// Test de toutes les fonctions
	testAll();

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(false);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 443);

    envoyer_recevoir("login 11800672 \"BRUN-COSME-GAZOT\"", reponse);

	// Charge l'épreuve et affiche le message
    envoyer_recevoir("load Northwoods", reponse);
    envoyer_recevoir("start", reponse);
	printf("%s\n==========================================================\n", reponse);

	// Envoi le mot de passe et affiche la réponse decrypté
    envoyer_recevoir("hasta la victoria siempre", reponse);
	decrypteSeq(reponse);
	printf("%s\n==========================================================\n", reponse);

	// Recupère et renvoie le mot de passe donné puis affiche la réponse decrypté
	strcpy(password, reponse);
	cutString(password, 578, 597);
	envoyer_recevoir(password, reponse);
	decrypteSeq(reponse);
	printf("%s\n==========================================================\n", reponse);

	// Recupère, crypte, envoi le mot de passe et affiche la réponse decrypté
	strcpy(password, reponse);
	cutString(password, 417, 453);
	encrypteSeq(password);
	envoyer_recevoir(password, reponse);
	cutString(reponse, 24, 1036);
	decrypteSeq(reponse);
	printf("%s\n==========================================================\n", reponse);

    lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(message, reponse); // on envoie message, et on reçoit la réponse du serveur

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");

    return 0;
}
