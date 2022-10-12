
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "asserts.h"
#include "listes.h"


int testAjouterEnTete(void) {
	sequence_t* seq = nouvelleSequence();
	ajouterEnTete(seq, 'A');
	assert(seq->tete->command == 'A');
	printf("SUIVANT : %p\n", seq->tete->suivant);
	assert(seq->tete->suivant == NULL);
	ajouterEnTete(seq, 'B');
	assert(seq->tete->command == 'B');
	assert(seq->tete->suivant->command == 'A');
	assert(seq->tete->suivant->suivant == NULL);
	return 0;
}


int testAjouterEnQueue(void) {
	sequence_t* seq = nouvelleSequence();
	ajouterEnQueue(seq, 'A');
	assert(seq->tete->command == 'A');
	assert(seq->tete->suivant == NULL);
	ajouterEnQueue(seq, 'B');
	assert(seq->tete->command == 'A');
	assert(seq->tete->suivant->command == 'B');
	assert(seq->tete->suivant->suivant == NULL);
	return 0;
}


int testConversion(void) {
	char * texte = "ABCD";
	sequence_t* seq = nouvelleSequence();
	conversion(texte, seq);
	assert(seq->tete->command == 'A');
	assert(seq->tete->suivant->command == 'B');
	assert(seq->tete->suivant->suivant->command == 'C');
	assert(seq->tete->suivant->suivant->suivant->command == 'D');
	assert(seq->tete->suivant->suivant->suivant->suivant == NULL);
	return 0;
}


int testAll(void) {
	testAjouterEnTete();
	testAjouterEnQueue();
	testConversion();
	return 0;
}
