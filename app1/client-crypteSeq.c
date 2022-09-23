#include "client.h"
#include "ressources.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAXMSG MAXREP

int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    char message[MAXMSG]; // pour stocker le message à envoyer au serveur
	char copyMessage[MAXMSG];
	char* copyMessageCut = (char*) malloc(MAXMSG * sizeof(char));

	// Test de toutes les fonctions
	testFunctions();

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(false);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 443);

    envoyer_recevoir("login 11800672 \"BRUN-COSME-GAZOT\"", reponse);

	// Charge l'épreuve et affiche la réponse
    envoyer_recevoir("load crypteSeq", reponse);
	decrypteMove(reponse);
	printf("%s\n==========================================================\n", reponse);

	// Démarre l'épreuve, décrypte la réponse avec decrypteMove et l'affiche
	envoyer_recevoir("start", reponse);
	decrypteMove(reponse);
	printf("%s\n==========================================================\n", reponse);

	// On crypte la reponse avec crypteSeq et on l'envoit
	strcpy(copyMessage, reponse);
	encrypteSeq(copyMessage);
	envoyer_recevoir(copyMessage, reponse);

	// On décrypte la réponse avec decrypteSeq et on l'affiche
	strcpy(copyMessage, reponse);
	copyMessageCut = deleteFirstLines(copyMessage, 2);
	decrypteSeq(copyMessageCut);
	printf("%s\n==========================================================\n", copyMessageCut);


    lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(message, reponse); // on envoie message, et on reçoit la réponse du serveur

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");

    return 0;
}
