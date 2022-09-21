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

	// Test de toutes les fonctions
	testFunctions();

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(false);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */


    envoyer_recevoir("login 11800672 \"BRUN-COSME-GAZOT\"", reponse);

    envoyer_recevoir("load TUTORIEL", reponse);
    envoyer_recevoir("depart", reponse);
    envoyer_recevoir("OK", reponse);
    envoyer_recevoir("OUI", reponse);

	// Renvoi les 6 prochaines réponses en caplock
	int i;
	for (i = 0; i < 6; i++) {
		envoyer_recevoir(capitalize(reponse), reponse);
		printf("%s", reponse);
	}


    lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(message, reponse); // on envoie message, et on reçoit la réponse du serveur

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}
