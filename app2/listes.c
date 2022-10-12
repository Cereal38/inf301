#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"


/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

bool silent_mode = false;


// --- Start sequences --- //
sequence_t* nouvelleSequence(void)
{
	sequence_t* seq = (sequence_t*) malloc(sizeof(sequence_t));
	seq->tete = NULL;
	return seq;
}

cellule_t* nouvelleCellule (void)
{
	cellule_t * cel = (cellule_t*) malloc (sizeof (cellule_t));
    return cel;
}


void detruireCellule (cellule_t* cel)
{
	free (cel);
}

void ajouterEnTete (sequence_t * liste, char val)
{
	cellule_t * new = nouvelleCellule ();
	new->command = val;
	new->suivant = liste->tete;
	liste->tete = new;
}


void ajouterEnQueue (sequence_t * liste, char val)
{
	cellule_t * new = nouvelleCellule ();
	cellule_t * cel = nouvelleCellule ();
	new->command = val;
	new->suivant = NULL;
	if (liste->tete == NULL)
		liste->tete = new;
	else
	{
		cel = liste->tete;
		while (cel->suivant != NULL)
			cel = cel->suivant;
		cel->suivant = new;
	}
}


void conversion (char *texte, sequence_t *seq)
{

	seq->tete = NULL;

	int i = 0;
	while (texte[i] != '\0')
	{
		ajouterEnQueue (seq, texte[i]);
		i++;
	}
}


void afficher (sequence_t* seq)
{
    assert (seq); /* Le pointeur doit être valide */

	cellule_t * cel = nouvelleCellule();
	cel = seq->tete;
	while (cel != NULL)
	{
		printf ("%c", cel->command);
		cel = cel->suivant;
	}
	printf ("\n");
}
// --- End sequences --- //


// --- Start piles --- //
pile_t* nouvellePile(void)
{
	pile_t* pile = (pile_t*) malloc(sizeof(pile_t));
	pile->tete = NULL;
	return pile;
}

void empiler (pile_t * pile, int val)
{
	element_t * new = (element_t*) malloc (sizeof (element_t));
	new->val = val;
	new->suivant = pile->tete;
	pile->tete = new;
}

int depiler (pile_t * pile)
{
	int val;
	element_t * element = (element_t*) malloc (sizeof (element_t));
	element = pile->tete;
	val = element->val;
	pile->tete = element->suivant;
	free (element);
	return val;
}

void additionner (pile_t * pile)
{
	char val1 = depiler (pile);
	char val2 = depiler (pile);
	empiler (pile, val1 + val2);
}

void soustraire (pile_t * pile)
{
	char val1 = depiler (pile);
	char val2 = depiler (pile);
	empiler (pile, val1 - val2);
}

void multiplier (pile_t * pile)
{
	char val1 = depiler (pile);
	char val2 = depiler (pile);
	empiler (pile, val1 * val2);
}

void afficherPile (pile_t * pile)
{
	element_t * element = (element_t*) malloc (sizeof (element_t));
	element = pile->tete;
	while (element != NULL)
	{
		printf ("%d ", element->val);
		element = element->suivant;
	}
	printf ("\n");
}

int convertCharToInt (char c)
{
	return c - '0';
}
// --- End piles --- //
