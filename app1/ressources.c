#include "ressources.h"
#include "client.h"
#include <ctype.h>
#include <string.h>
#include <assert.h>


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


void concatenateFromLeft(char* str1, char* str2) { 
	int lenStr1;
	int lenStr2 = strlen(str2);
	int i;
	int j;
	for (i = 0; i < lenStr2; i++) {
		lenStr1 = strlen(str1);
		for (j = lenStr1; j >= 0; j--) {
			str1[j + 1] = str1[j];
		}
	}
	for (i = 0; i < lenStr2; i++) {
		str1[i] = str2[i];
	}
}


int lenString(char* str) {
	int i = 0;
	while (str[i] != '\0') { i++; }
	return i;
}


void copyLastChars(char* str1, char* str2, int n) {
	int i = lenString(str2);
	int j = 0;
	i -= n;
	while (str2[i] != '\0') {
		str1[j] = str2[i];
		i++;
		j++;
	}
	str1[j] = '\0';
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


void decrypteMove(char* str) {

	// On créé les variables
	char DEC[MAXREP];
	char tempString[9];
	char lastChar[2]; lastChar[1] = '\0';
	int x;
	int lenStr;
	int lenDec = 0;

	// On récupère la longueur de str
	lenStr = lenString(str);

	// On boucle tant qu'il reste des caractères à décrypter
	while (lenStr > 0) {

		// On récupère le dernier caractère de str
		lastChar[0] = str[lenStr - 1];

		// On calcul x le modulo 8 du code ascii de lastChar
		x = lastChar[0] % 8;

		// Si len(DEC) est plus grande que x
		if (lenDec > x) {
			
			// On copie les x derniers char de DEC dans tempString
			copyLastChars(tempString, DEC, x);

			// On supprime les x derniers char de DEC
			DEC[lenDec - x] = '\0';

			// On insère la chaîne récupéré au début de DEC
			concatenateFromLeft(DEC, tempString);

		}

		// On insère lastChar au début de DEC
		concatenateFromLeft(DEC, lastChar);

		// Décrémente len
		lenStr--;
		lenDec++;

	}

	// On met DEC dans le message de base
	strcpy(str, DEC);

}


void testFunctions() {

	char str1[100];
	char str2[100];
	char c;


	printf("TEST [");


	// capitalize
	str1[0] = 'a';
	str1[1] = 'b';
	str1[2] = 'c';
	str1[3] = '\0';
	assert(strcmp(capitalize(str1), "ABC") == 0);
	printf("#");

	
	// deleteFirstChar
	str1[0] = 'a';
	str1[1] = 'b';
	str1[2] = 'c';
	str1[3] = '\0';
	deleteFirstChar(str1);
	assert(strcmp(str1, "bc") == 0);
	printf("#");
	

	// concatenateFromRight
	str1[0] = 'a';
	str1[1] = 'b';
	str1[2] = 'c';
	str1[3] = '\0';
	str2[0] = 'd';
	str2[1] = 'e';
	str2[2] = 'f';
	str2[3] = 'g';
	str2[4] = '\0';
	concatenateFromRight(str1, str2);
	assert(strcmp(str1, "abcdefg") == 0);
	printf("#");


	// concatenateFromLeft
	str1[0] = 'a';
	str1[1] = 'b';
	str1[2] = 'c';
	str1[3] = '\0';
	str2[0] = 'd';
	str2[1] = 'e';
	str2[2] = 'f';
	str2[3] = 'g';
	str2[4] = '\0';
	concatenateFromLeft(str1, str2);
	assert(strcmp(str1, "defgabc") == 0);
	str1[0] = 'a';
	str1[1] = 'b';
	str1[2] = 'c';
	str1[3] = '\0';
	str2[0] = 'd';
	str2[1] = '\0';
	concatenateFromLeft(str1, str2);
	assert(strcmp(str1, "dabc") == 0);
	printf("#");


	// lenString
	str1[0] = 'a';
	str1[1] = 'b';
	str1[2] = 'c';
	str1[3] = '\0';
	assert(lenString(str1) == 3);
	printf("#");


	// copyLastChars
	str1[0] = 'a';
	str1[1] = 'b';
	str1[2] = 'c';
	str1[3] = '\0';
	str2[0] = 'd';
	str2[1] = 'e';
	str2[2] = 'f';
	str2[3] = 'g';
	str2[4] = '\0';
	copyLastChars(str1, str2, 2);
	assert(strcmp(str1, "fg") == 0);
	printf("#");


	// cesarDecodeChar
	c = 'g';
	assert(cesarDecodeChar(c) == 'b');
	c = 'G';
	assert(cesarDecodeChar(c) == 'B');
	c = 'b';
	assert(cesarDecodeChar(c) == 'w');
	printf("#");


	// cesarDecodeString
	str1[0] = 'G';
	str1[1] = 't';
	str1[2] = 'g';
	str1[3] = '\0';
	cesarDecodeString(str1);
	assert(strcmp(str1, "Bob") == 0);
	printf("#");


	// encrypteMove
	str1[0] = 'P';
	str1[1] = 'e';
	str1[2] = 't';
	str1[3] = 'i';
	str1[4] = 't';
	str1[5] = ' ';
	str1[6] = 'm';
	str1[7] = 'e';
	str1[8] = 's';
	str1[9] = 's';
	str1[10] = 'a';
	str1[11] = 'g';
	str1[12] = 'e';
	str1[13] = ' ';
	str1[14] = 'c';
	str1[15] = 'o';
	str1[16] = 'u';
	str1[17] = 'r';
	str1[18] = 't';
	str1[19] = '.';
	str1[20] = '\0';
	encrypteMove(str1);
	assert(strcmp(str1, "Pee ct mosusriae.ttg") == 0);
	printf("#");

	// decrypteMove
	str1[0] = 'P';
	str1[1] = 'e';
	str1[2] = 'e';
	str1[3] = ' ';
	str1[4] = 'c';
	str1[5] = 't';
	str1[6] = ' ';
	str1[7] = 'm';
	str1[8] = 'o';
	str1[9] = 's';
	str1[10] = 'u';
	str1[11] = 's';
	str1[12] = 'r';
	str1[13] = 'i';
	str1[14] = 'a';
	str1[15] = 'e';
	str1[16] = '.';
	str1[17] = 't';
	str1[18] = 't';
	str1[19] = 'g';
	str1[20] = '\0';
	decrypteMove(str1);
	assert(strcmp(str1, "Petit message court.") == 0);
	printf("#");

	printf("]\n\n### ALL TEST PASSED ###\n\n");

}
