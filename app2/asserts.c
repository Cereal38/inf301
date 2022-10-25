
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

	sequence_t * seq = nouvelleSequence();
	ajouterEnTete(seq, 'A');
	ajouterEnTete(seq, 'B');

	pile_t * pile = nouvellePile();
	empiler(pile, (valeurPile) 1, INT);
	empiler(pile, (valeurPile) 'a', CHAR);
	empiler(pile, (valeurPile) seq, BLOC);

	assert(pile->tete->valeur.s == seq);
	assert(pile->tete->valeur.s->tete->command == 'B');
	assert(pile->tete->valeur.s->tete->suivant->command == 'A');
	assert(pile->tete->suivant->valeur.c == 'a');
	assert(pile->tete->suivant->suivant->valeur.i == 1);
	return 0;
}


int testDepiler(void) {
	pile_t * pile = nouvellePile();
	empiler(pile, (valeurPile) 1, INT);
	empiler(pile, (valeurPile) 'a', CHAR);
	empiler(pile, (valeurPile) 2, INT);

	assert(depiler(pile)->valeur.i == 2);
	assert(depiler(pile)->valeur.c == 'a');
	assert(depiler(pile)->type == INT);
	return 0;
}



void testAdditionner(void) {
	pile_t * pile = nouvellePile();
	empiler(pile, (valeurPile) 1, INT);
	empiler(pile, (valeurPile) 2, INT);
	empiler(pile, (valeurPile) 3, INT);
	additionner(pile);
	assert(pile->tete->valeur.i == 5);
	assert(pile->tete->suivant->valeur.i == 1);
	assert(pile->tete->suivant->suivant == NULL);
}


void testSoustraire(void) {
	pile_t * pile = nouvellePile();
	empiler(pile, (valeurPile) 1, INT);
	empiler(pile, (valeurPile) 2, INT);
	empiler(pile, (valeurPile) 3, INT);
	soustraire(pile);
	assert(pile->tete->valeur.i == 1);
	assert(pile->tete->suivant->valeur.i == 1);
	assert(pile->tete->suivant->suivant == NULL);
}


void testMultiplier(void) {
	pile_t * pile = nouvellePile();
	empiler(pile, (valeurPile) 1, INT);
	empiler(pile, (valeurPile) 2, INT);
	empiler(pile, (valeurPile) 3, INT);
	multiplier(pile);
	assert(pile->tete->valeur.i == 6);
	assert(pile->tete->suivant->valeur.i == 1);
	assert(pile->tete->suivant->suivant == NULL);
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


void testInverseDeuxPremiers(void) {
	pile_t * pile = nouvellePile();
	empiler(pile, (valeurPile) 1, INT);
	empiler(pile, (valeurPile) 2, INT);
	empiler(pile, (valeurPile) 3, INT);
	inverseDeuxPremiers(pile);
	assert(pile->tete->valeur.i == 2);
	assert(pile->tete->suivant->valeur.i == 3);
	assert(pile->tete->suivant->suivant->valeur.i == 1);
	assert(pile->tete->suivant->suivant->suivant == NULL);
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
	testInverseDeuxPremiers();
	return 0;
}
