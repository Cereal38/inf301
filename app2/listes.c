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
}
// --- End sequences --- //


// --- Start piles --- //
pile_t* nouvellePile(void)
{
	pile_t* pile = (pile_t*) malloc(sizeof(pile_t));
	pile->tete = NULL;
	return pile;
}

void empiler (pile_t * pile, valeurPile val, typeElement type)
{
	element_t * new = (element_t*) malloc (sizeof (element_t));
	new->valeur = val;
	new->type = type;
	new->suivant = pile->tete;
	pile->tete = new;
}

element_t* depiler (pile_t * pile)
{
	element_t * cel = (element_t*) malloc (sizeof (element_t));
	cel = pile->tete;
	pile->tete = cel->suivant;
	return cel;
}

void additionner (pile_t * pile)
{
	element_t * cel1 = (element_t*) malloc (sizeof (element_t));
	element_t * cel2 = (element_t*) malloc (sizeof (element_t));
	cel1 = depiler (pile);
	cel2 = depiler (pile);
	empiler(pile, (valeurPile) (cel1->valeur.i + cel2->valeur.i), INT);

}

void soustraire (pile_t * pile)
{
	element_t * cel1 = (element_t*) malloc (sizeof (element_t));
	element_t * cel2 = (element_t*) malloc (sizeof (element_t));
	cel1 = depiler (pile);
	cel2 = depiler (pile);
	empiler(pile, (valeurPile) (cel1->valeur.i - cel2->valeur.i), INT);
}

void multiplier (pile_t * pile)
{
	element_t * cel1 = (element_t*) malloc (sizeof (element_t));
	element_t * cel2 = (element_t*) malloc (sizeof (element_t));
	cel1 = depiler (pile);
	cel2 = depiler (pile);
	empiler(pile, (valeurPile) (cel1->valeur.i * cel2->valeur.i), INT);
}

void afficherPile (pile_t * pile)
{
	element_t * cel = (element_t*) malloc (sizeof (element_t));
	cel = pile->tete;
	while (cel != NULL)
	{

		// L'affichage diffère en fonction du type de la variable
		switch (cel->type)
		{
			case INT:
				printf ("%d ", cel->valeur.i);
				break;
			case CHAR:
				printf ("%c ", cel->valeur.c);
				break;
			case BLOC :
				printf("{");
				afficher(cel->valeur.s);
				printf("}");
				break;
			default:
				break;
		}

		cel = cel->suivant;
	}
	printf ("\n");
}

int convertCharToInt (char c)
{
	return c - '0';
}
// --- End piles --- //
