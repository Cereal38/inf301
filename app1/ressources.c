#include "ressources.h"
#include "client.h"
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


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


int indexPreviousChar(char* str, char c) {
	/* Renvoit la position du caractère précédent c, ou -1 si c n'est pas dans str */

	int index = 0;

	// On récupère l'index du caractère c (s'il existe)
	while ((str[index] != c) && (str[index] != '\0')) { index++; }

	if ((str[index] == c) && (index != 0)) { index--; }
	else if (index == 0) { index = lenString(str) - 1; }
	else { index = -1; }

	return index;
}


int indexNextChar(char* str, char c) {
	/* Renvoit la position du caractère suivant c, ou -1 si c n'est pas dans str */

	int index = 0;
	int indexLastChar = lenString(str) - 1;

	// On récupère l'index du caractère c (s'il existe)
	while ((str[index] != c) && (str[index] != '\0')) { index++; }

	if ((str[index] == c) && (index != indexLastChar)) { index++; }
	else if (index == indexLastChar) { index = 0; }
	else { index = -1; }

	return index;
}


char popFirstChar(char* str) {
	char c = str[0];
	deleteFirstChar(str);
	return c;
}


void moveCharToEnd(char* str, char c) {
	// Permet d'obtenir la première position du char dans la chaîne
	int index = 0;
	while (str[index] != c && str[index] != '\0') {
		index++;
	}

	// Si le char n'est pas présent dans la chaîne on n'exécute pas la suite
	if (str[index] == c) { 
		
		int len = lenString(str);

		// Décale tout les caractères après la postion trouvé de 1 vers la gauche
		int i = index;
		while (i < len) {
			str[i] = str[i + 1];
			i++;
		}

		// On insère le caractère à la fin de la chaîne
		str[len - 1] = c;

	}
}


int isCharInString(char* str, char c) {
	int i = 0;
	while (str[i] != '\0') {
		if (str[i] == c) { return 1; }
		i++;
	}
	return 0;
}


void appendChar(char* str, char c) {
	int len = lenString(str);
	str[len] = c;
	str[len + 1] = '\0';
}


void clearString(char* str, int len) {
	for (int i = 0; i < len; i++) { str[i] = '\0'; }
}


char* deleteFirstLines(char* str, int n) {
	int i = 0;
	while (n > 0 && str[0] != '\0') {
		if (str[i] == '\n') { n--; }
		i++;
	}
	return &str[i];
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
	char* ENC = (char*) malloc(MAXREP * sizeof(char));
	clearString(ENC, MAXREP);
	char tempString[9];
	char c;
	int x;
	int i;
	int posENC = 0;
	int len;
	int lenSave;

	// On récupère la longueur de str
	len = lenString(str);
	lenSave = len;


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

	// On termine la chaîne pour éviter une erreur de mémoire
	str[lenSave] = '\0';

	// On libère la mémoire
	free(ENC);

}


void decrypteMove(char* str) {

	// On créé les variables
	char* DEC = (char*) malloc(MAXREP * sizeof(char));
	clearString(DEC, MAXREP);
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

	// On libère la mémoire
	free(DEC);

}


void encrypteSeq(char* str) {

	// On créé les variables
	char* enc = (char*) malloc(MAXREP * sizeof(char));
	clearString(enc, MAXREP);
	char* seq = (char*) malloc(1000 * sizeof(char));
	clearString(seq, 1000);
	char c;
	int indexPrev = 0;

	// On parcours la chaîne et on applique l'algo à chaque caractère
	int i = 0;
	while (str[i] != '\0') {

		// On récupère le caractère
		c = str[i];

		// On regarde si le caractère se trouve dans seq et on procède en conséquent
		if (isCharInString(seq, c)) {

			// Si le caractère est déjà dans seq, on recupère l'index du caractère précédent
			indexPrev = indexPreviousChar(seq, c);

			// On ajoute le caractère précédent c à la fin de enc
			appendChar(enc, seq[indexPrev]);

			// On déplace le caractère c à la fin de seq
			moveCharToEnd(seq, c);

		} else {

			// Si le caractère n'est pas dans seq, on l'ajoute
			appendChar(seq, c);

			// On ajoute le caractère à enc
			appendChar(enc, c);

		}

		i++;

	}

	// On met enc dans le message de base
	strcpy(str, enc);

	// On libère la mémoire
	free(enc);
	free(seq);

}


void decrypteSeq(char* str) {

	// On créé les variables
	char* dec = (char*) malloc(MAXREP * sizeof(char));
	clearString(dec, MAXREP);
	char* seq = (char*) malloc(1000 * sizeof(char));
	clearString(seq, 1000);
	char c;
	char cDecrypt;
	int indexSuiv = 0;

	// On parcours la chaîne et on applique l'algo à chaque caractère
	int i = 0;
	while (str[i] != '\0') {

		// On récupère le caractère
		c = str[i];

		// On regarde si le caractère se trouve dans seq et on procède en conséquent
		if (isCharInString(seq, c)) {

			// Si le caractère est déjà dans seq, on recupère le caractère suivant
			indexSuiv = indexNextChar(seq, c);
			cDecrypt = seq[indexSuiv];

			// On ajoute le caractère suivant c à la fin de dec
			appendChar(dec, cDecrypt);

			// On déplace le caractère suivant c à la fin de seq
			moveCharToEnd(seq, cDecrypt);

		} else {

			// Si le caractère n'est pas dans seq, on l'ajoute
			appendChar(seq, c);

			// On ajoute le caractère à dec
			appendChar(dec, c);

		}

		i++;

	}

	// On met dec dans le message de base
	strcpy(str, dec);

	// On libère la mémoire
	free(dec);
	free(seq);

}



void testFunctions() {

	char str1[100];
	char str2[100];
	char* str3 = (char*) malloc(100 * sizeof(char));
	char c;


	printf("TEST [");


	// capitalize
	strcpy(str1, "abc");
	assert(strcmp(capitalize(str1), "ABC") == 0);
	printf("#");

	
	// deleteFirstChar
	strcpy(str1, "abc");
	deleteFirstChar(str1);
	assert(strcmp(str1, "bc") == 0);
	printf("#");
	

	// concatenateFromRight
	strcpy(str1, "abc");
	strcpy(str2, "defg");
	concatenateFromRight(str1, str2);
	assert(strcmp(str1, "abcdefg") == 0);
	printf("#");


	// concatenateFromLeft
	strcpy(str1, "abc");
	strcpy(str2, "defg");
	concatenateFromLeft(str1, str2);
	assert(strcmp(str1, "defgabc") == 0);
	strcpy(str1, "abc");
	strcpy(str2, "d");
	concatenateFromLeft(str1, str2);
	assert(strcmp(str1, "dabc") == 0);
	printf("#");


	// lenString
	strcpy(str1, "abc");
	assert(lenString(str1) == 3);
	printf("#");


	// copyLastChars
	strcpy(str1, "abc");
	strcpy(str2, "defg");
	copyLastChars(str1, str2, 2);
	assert(strcmp(str1, "fg") == 0);
	printf("#");


	// indexPreviousChar
	strcpy(str1, "abc");
	assert(indexPreviousChar(str1, 'a') == 2);
	assert(indexPreviousChar(str1, 'b') == 0);
	assert(indexPreviousChar(str1, 'z') == -1);
	printf("#");


	// indexNextChar
	strcpy(str1, "abc");
	assert(indexNextChar(str1, 'a') == 1);
	assert(indexNextChar(str1, 'c') == 0);
	assert(indexNextChar(str1, 'z') == -1);
	printf("#");


	// popFirstChar
	strcpy(str1, "abc");
	c = popFirstChar(str1);
	assert(c == 'a');
	assert(strcmp(str1, "bc") == 0);
	printf("#");


	// moveCharToEnd
	strcpy(str1, "abcdefg");
	c = 'd';
	moveCharToEnd(str1, c);
	assert(strcmp(str1, "abcefgd") == 0);
	strcpy(str1, "abcdefg");
	c = 'g';
	moveCharToEnd(str1, c);
	assert(strcmp(str1, "abcdefg") == 0);
	strcpy(str1, "abcdefg");
	c = 'h';
	moveCharToEnd(str1, c);
	assert(strcmp(str1, "abcdefg") == 0);
	printf("#");


	// isCharInString
	strcpy(str1, "abc");
	assert(isCharInString(str1, 'a') == 1);
	assert(isCharInString(str1, 'b') == 1);
	assert(isCharInString(str1, 'c') == 1);
	assert(isCharInString(str1, 'd') == 0);
	printf("#");


	// appendChar
	strcpy(str1, "abc");
	appendChar(str1, 'd');
	assert(strcmp(str1, "abcd") == 0);
	strcpy(str1, "");
	appendChar(str1, 'a');
	assert(strcmp(str1, "a") == 0);
	printf("#");


	// clearString
	strcpy(str1, "abc");
	clearString(str1, 3);
	assert(strcmp(str1, "") == 0);
	printf("#");


	// deleteFirstLines
	strcpy(str1, "abc\ndef\nghi\njkl");
	str3 = deleteFirstLines(str1, 2);
	assert(strcmp(str3, "ghi\njkl") == 0);
	strcpy(str1, "abc\ndef\nghi\njkl");
	str3 = deleteFirstLines(str3, 0);
	assert(strcmp(str1, "abc\ndef\nghi\njkl") == 0);
	strcpy(str1, "abc\ndef\nghi\njkl");
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
	strcpy(str1, "Gtg");
	cesarDecodeString(str1);
	assert(strcmp(str1, "Bob") == 0);
	printf("#");


	// encrypteMove
	strcpy(str1, "Petit message court.");
	encrypteMove(str1);
	assert(strcmp(str1, "Pee ct mosusriae.ttg") == 0);
	printf("#");


	// decrypteMove
	strcpy(str1, "Pee ct mosusriae.ttg");
	decrypteMove(str1);
	assert(strcmp(str1, "Petit message court.") == 0);
	printf("#");


	// encrypteSeq
	strcpy(str1, "abcbcca");
	encrypteSeq(str1);
	assert(strcmp(str1, "abcaabc") == 0);
	printf("#");
	

	// decrypteSeq
	strcpy(str1, "abcaabc");
	decrypteSeq(str1);
	assert(strcmp(str1, "abcbcca") == 0);
	printf("#");
	

	printf("]\n\n### ALL TEST PASSED ###\n\n");

}
