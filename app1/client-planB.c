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
	int shift;
	char password[100];
	strcpy(password, "hasta la revolucion");

	// Test de toutes les fonctions
	testAll();

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(false);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */


    envoyer_recevoir("login 11800672 \"BRUN-COSME-GAZOT\"", reponse);

	// Charge l'épreuve et affiche le message
    envoyer_recevoir("load planB", reponse);
	printf("%s\n==========================================================\n", reponse);

	// Affiche le message d'aide décrypté et recupère la valeur du décalage
	envoyer_recevoir("aide", reponse);
	shift = reponse[0] - 'C';
	cesarDecodeString(reponse, shift);
	printf("%s\n==========================================================\n", reponse);

	// Démarre le challenge et affiche la réponse
	envoyer_recevoir("start", reponse);
	printf("%s\n==========================================================\n", reponse);

	// Envoi le mot de passe crypté et affiche la réponse decrypté
	cesarDecodeString(password, (26-shift)*-1);
	envoyer_recevoir(password, reponse);
	cesarDecodeString(reponse, shift);
	printf("%s\n==========================================================\n", reponse);


    lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(message, reponse); // on envoie message, et on reçoit la réponse du serveur

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}
