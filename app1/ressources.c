#include "ressources.h"
#include "asserts.h"
#include "client.h"
#include <ctype.h>
#include <string.h>
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


void cutString(char* str, int start, int end) {
	/* Découpe la chaîne. start et end inclus */
	int i;
	for (i = 0; i < start; i++) { deleteFirstChar(str); end--; }
	str[end+1] = '\0';
}


char cesarDecodeChar(char c, int shift) {

	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {

		if (shift > 0) {
			for (int i = 0; i < shift; i++) {
				if (c != 'a' && c != 'A') { c--; }
				else if (c == 'a') { c = 'z'; }
				else if (c == 'A') { c = 'Z'; }
			}
		}

		else if (shift < 0) {
			for (int i = 0; i > shift; i--) {
				if (c != 'z' && c != 'Z') { c++; }
				else if (c == 'z') { c = 'a'; }
				else if (c == 'Z') { c = 'A'; }
			}
		}
	}

	return c;

}


void cesarDecodeString(char *string, int shift) {

	for (int i = 0; string[i]; i++) {
		string[i] = cesarDecodeChar(string[i], shift);
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


Head decrypteMoveLinkedList(Head * crypted) {

	// On créé les variables
	char lastChar;
	char tempChar;
	int x;
	int i;
	Head decrypted;
	decrypted = initLinkedList();

	// On boucle tant qu'il reste des caractères à décrypter
	while (crypted->len > 0) {

		// On récupère le dernier caractère de crypted
		lastChar = crypted->last->data;
		removeNodeEnd(crypted);

		// On calcul x le modulo 8 du code ascii de lastChar
		x = lastChar % 8;

		// Si len de decrypted est plus grande que x
		if (decrypted.len > x) {
			
			// On déplace les x derniers char de decrypted au début
			for (i = 0; i < x; i++) {
				tempChar = decrypted.last->data;
				removeNodeEnd(&decrypted);
				addNodeStart(&decrypted, tempChar);
			}

		}

		// On insère lastChar au début de decrypted 
		addNodeStart(&decrypted, lastChar);

	}

	return decrypted;
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


void encrypteAssoc(char* str) {

	// On créé les variables
	char* enc = (char*) malloc(MAXREP * sizeof(char));
	clearString(enc, MAXREP);
	char* seq = (char*) malloc(1000 * sizeof(char));
	clearString(seq, 1000);
	char* assoc = (char*) malloc(1000 * sizeof(char));
	clearString(assoc, 1000);
	char c;
	char tempChar;
	int indexPrev = 0;
	int indexCurrent = 0;

	// On parcours la chaîne et on applique l'algo à chaque caractère
	int i = 0;
	while (str[i] != '\0') {

		// On récupère le caractère
		c = str[i];

		// On regarde si le caractère se trouve dans seq et on procède en conséquent
		if (isCharInString(seq, c)) {

			// Si le caractère est déjà dans seq, on recupère l'index du caractère précédent
			indexPrev = indexPreviousChar(seq, c);

			// On récupère également l'index du caractère actuel
			indexCurrent = indexNextChar(seq, seq[indexPrev]);

			// On inverse les 2 associations
			tempChar = assoc[indexPrev];
			assoc[indexPrev] = assoc[indexCurrent];
			assoc[indexCurrent] = tempChar;
			
			// On ajoute le caractère précédent associé à la fin de enc
			appendChar(enc, assoc[indexCurrent]);

			// On déplace le caractère c ainsi que son association à la fin de leur séquence
			moveCharToEnd(seq, c);
			moveCharToEnd(assoc, assoc[indexCurrent]);

		} else {

			// Si le caractère n'est pas dans seq, on l'ajoute
			appendChar(seq, c);

			// On ajoute l'association dans assoc
			appendChar(assoc, c);

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


void decrypteAssoc(char* str) {

	// On créé les variables
	char* dec = (char*) malloc(MAXREP * sizeof(char));
	clearString(dec, MAXREP);
	char* seq = (char*) malloc(1000 * sizeof(char));
	clearString(seq, 1000);
	char* assoc = (char*) malloc(1000 * sizeof(char));
	clearString(assoc, 1000);
	char c;
	char cDecrypt;
	char tempAssoc;
	int indexSuiv = 0;
	int indexCurrent = 0;

	// On parcours la chaîne et on applique l'algo à chaque caractère
	int i = 0;
	while (str[i] != '\0') {

		// On récupère le caractère
		c = str[i];

		// On regarde si le caractère se trouve dans seq et on procède en conséquent
		if (isCharInString(seq, c)) {

			// Si le caractère est déjà dans seq, on recupère son index et l'index suivant
			indexSuiv = indexNextChar(seq, c);
			indexCurrent = indexPreviousChar(seq, seq[indexSuiv]);

			// On inverse les 2 associations
			tempAssoc = assoc[indexCurrent];
			assoc[indexCurrent] = assoc[indexSuiv];
			assoc[indexSuiv] = tempAssoc;

			// On récupère la valeur associée à c
			cDecrypt = assoc[indexCurrent];

			// On ajoute le caractère suivant c à la fin de dec
			appendChar(dec, cDecrypt);

			// On déplace le caractère suivant c et son association à la fin de leur séquence
			moveCharToEnd(assoc, assoc[indexCurrent]);
			moveCharToEnd(seq, c);

		} else {

			// Si le caractère n'est pas dans seq, on l'ajoute
			appendChar(seq, c);

			// On ajoute également son association dans assoc
			appendChar(assoc, c);

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



Head initLinkedList(void) {
	Head * head = (Head *) malloc(sizeof(Head));
	head->len = 0;
	head->first = NULL;
	head->last = NULL;
	return *head;
}


void addNodeStart(Head * head, char data) {
	Node * new = (Node *) malloc(sizeof(Node));
	new->data = data;
	new->next = head->first;
	new->prev = NULL;
	if (head->len > 0) { head->first->prev = new; }
	head->first = new;
	if (head->len == 0) { head->last = new; }
	head->len = head->len + 1;
}


void addNodeEnd(Head * head, char data) {
	Node * new = (Node *) malloc(sizeof(Node));
	new->data = data;
	new->next = NULL;
	new->prev = head->last;
	if (head->len > 0) { head->last->next = new; }
	head->last = new;
	if (head->len == 0) { head->first = new; }
	head->len = head->len + 1;
}


void removeNodeStart(Head * head) {
	
	if (head->len > 2) {
		head->first = head->first->next;
		free(head->first->prev);
		head->first->prev = NULL;
		head->len = head->len - 1;
	}

	else if (head->len == 2) {
		head->last->next = NULL;
		head->last->prev = NULL;
		free(head->first);
		head->first = head->last;
		head->len = 1;
	}

	else if (head->len == 1) {
		free(head->first);
		head->first = NULL;
		head->last = NULL;
		head->len = 0;
	}

}


void removeNodeEnd(Head * head) {

	if (head->len > 2) {
		head->last = head->last->prev;
		free(head->last->next);
		head->last->next = NULL;
		head->len = head->len - 1;
	}


	else if (head->len == 2) {
		head->last->next = NULL;
		head->last->prev = NULL;
		free(head->last);
		head->last = head->first;
		head->len = 1;
	}

	else if (head->len == 1) {
		free(head->last);
		head->first = NULL;
		head->last = NULL;
		head->len = 0;
	}

}


void printLinkedList(Head * head) {
	if (head->len == 0) { printf("List is empty...\n"); return; }
	Node * current = (Node *) malloc(sizeof(Node));
	current = head->first;
	printf("%c", current->data);
	while (current->next != NULL) {
		current = current->next;
		printf("%c", current->data);
	}
}
