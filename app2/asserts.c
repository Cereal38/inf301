
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "asserts.h"
#include "listes.h"


int testAjouterEnTete(void) {
	sequence_t* seq = nouvelleSequence();
	ajouterEnTete(seq, 'A');
	assert(seq->tete->command == 'A');
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


int testEmpiler(void) {
	pile_t* pile = nouvellePile();
	empiler(pile, 1);
	assert(pile->tete->val == 1);
	assert(pile->tete->suivant == NULL);
	empiler(pile, 2);
	assert(pile->tete->val == 2);
	assert(pile->tete->suivant->val == 1);
	assert(pile->tete->suivant->suivant == NULL);
	return 0;
}


int testDepiler(void) {
	pile_t* pile = nouvellePile();
	empiler(pile, 1);
	empiler(pile, 2);
	assert(depiler(pile) == 2);
	assert(depiler(pile) == 1);
	return 0;
}


void testAdditionner(void) {
	pile_t* pile = nouvellePile();
	empiler(pile, 1);
	empiler(pile, 2);
	empiler(pile, 2);
	additionner(pile);
	assert(depiler(pile) == 4);
	assert(depiler(pile) == 1);
}


void testSoustraire(void) {
	pile_t* pile = nouvellePile();
	empiler(pile, 1);
	empiler(pile, 2);
	empiler(pile, 3);
	soustraire(pile);
	assert(depiler(pile) == 1);
	assert(depiler(pile) == 1);
}


void testMultiplier(void) {
	pile_t* pile = nouvellePile();
	empiler(pile, 2);
	empiler(pile, 3);
	multiplier(pile);
	assert(depiler(pile) == 6);
}


void testConvertCharToInt(void) {
	assert(convertCharToInt('0') == 0);
	assert(convertCharToInt('1') == 1);
	assert(convertCharToInt('2') == 2);
	assert(convertCharToInt('3') == 3);
	assert(convertCharToInt('4') == 4);
	assert(convertCharToInt('5') == 5);
	assert(convertCharToInt('6') == 6);
	assert(convertCharToInt('7') == 7);
	assert(convertCharToInt('8') == 8);
	assert(convertCharToInt('9') == 9);
}


int testAll(void) {
	testAjouterEnTete();
	testAjouterEnQueue();
	testConversion();
	testEmpiler();
	testDepiler();
	testAdditionner();
	testSoustraire();
	testMultiplier();
	testConvertCharToInt();
	return 0;
}
