#include "client.h"
#include "ressources.h"
#include "asserts.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAXMSG MAXREP

int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    char message[MAXMSG]; // pour stocker le message à envoyer au serveur
	char string[150];
	char key[150];
	char pwDecryptedStr[150];
	Head pwCrypted;
	Head pwDecrypted;
	Node * currentNode = (Node *) malloc(sizeof(Node));
	int i;
	int j;

	// Test de toutes les fonctions
	testAll();

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(false);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 443);
    // utilisez le port 443 en cas de problème sur le 9999


    envoyer_recevoir("login 11800672 \"BRUN-COSME-GAZOT\"", reponse);

	// Charge l'épreuve, décrypte et affiche la réponse
    envoyer_recevoir("load OneMillion", reponse);
	decrypteMove(reponse);
	printf("%s\n==========================================================\n", reponse);

	// Recupère la chaine de 100 caractères
    envoyer_recevoir("aide", reponse);
	strcpy(string, reponse);

	// Démarre l'exercice et recupère la clé
    envoyer_recevoir("start", reponse);
	strcpy(key, reponse);

	// Créé la liste chaînée et la décrypte
	for (i = 0; i < 9999; i++) {
		for (j = 0; j < 100; j++) {
			addNodeEnd(&pwCrypted, string[j]);
		}
	}
	for (i = 0; i < 100; i++) {
		addNodeEnd(&pwCrypted, string[i]);
	}
	pwDecrypted = decrypteMoveLinkedList(&pwCrypted);

	// Récupère les 100 premiers caractères dans une string
	currentNode = pwDecrypted.first;
	for (i = 0; i < 100; i++) {
		pwDecryptedStr[i] = currentNode->data;
		currentNode = currentNode->next;
	}
	pwDecryptedStr[100] = '\0';

	// Envoie le mot de passe et affiche la réponse décrypté
    envoyer_recevoir(pwDecryptedStr, reponse);
	decrypteMove(reponse);
	printf("%s\n==========================================================\n", reponse);


    lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(message, reponse); // on envoie message, et on reçoit la réponse du serveur

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");

    return 0;
}
