#include "ressources.h"
#include "client.h"
#include <ctype.h>
#include <string.h>


char* capitalize(char *string) {
	for (int i = 0; string[i]; i++) {
		string[i] = toupper(string[i]);
	}
	return string;
}


void deleteFirstChar(char* str) {
	int i = 0;
	while (str[i] != '\0') {
		str[i] = str[i + 1];
		i++;
	}
}


void concatenateFromRight(char* str1, char* str2) {
	int i = 0;
	int j = 0;
	while (str1[i] != '\0') { i++; }
	while (str2[j] != '\0') {
		str1[i] = str2[j];
		i++;
		j++;
	}
	str1[i] = '\0';
}


int lenString(char* str) {
	int i = 0;
	while (str[i] != '\0') { i++; }
	return i;
}


char cesarDecodeChar(char c) {

	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		for (int i = 0; i < 5; i++) {
			if (c != 'a') {	c--; }
			else { c = 'z'; }
		}
	}

	return c;

}


void cesarDecodeString(char *string) {

	for (int i = 0; string[i]; i++) {
		string[i] = cesarDecodeChar(string[i]);
	}

}


void encrypteMove(char* str) {

	// On créé les variables
	char ENC[MAXREP];
	char tempString[9];
	char c;
	int x;
	int i;
	int posENC = 0;
	int len;

	// On récupère la longueur de str
	len = lenString(str);


	while (len > 0) {

		// On récupère c, le premier caractère de str pour le placer à la fin d'ENC
		c = str[0];
		ENC[posENC] = c;
		posENC++;

		// On supprime le premier caractère de str
		deleteFirstChar(str);

		// On calcul x, le code ascii de c modulo 8
		x = c % 8;

		// S'il reste au moins x caractères dans str
		if (x <= len) {

			// On copie les x premiers caractères de str dans tempString
			for (i = 0; i < x; i++) {
				tempString[i] = str[i];
			}
			tempString[i] = '\0';

			// On ajoute un '\0' à tempString là où on souhaite s'arrêter
			tempString[x] = '\0';

			// On supprime les x premiers caractères de str
			for (i = 0; i < x; i++) { deleteFirstChar(str); }

			// On ajoute la chaîne tempString à la fin de str
			concatenateFromRight(str, tempString);

		}

		// On réduit de 1 la variable contenant la taille de str
		len--;

	}

	// On met ENC dans le message de base
	strcpy(str, ENC);

}
