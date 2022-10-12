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

