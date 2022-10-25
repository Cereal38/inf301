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


cellule_t* nouvelleCellule (void)
{
	cellule_t* cel = (cellule_t*) malloc (sizeof(cellule_t));

    return cel;
}


void detruireCellule (cellule_t* cel)
{
	free (cel);
}


void empiler(sequence_t* seq, valeurPile val, typeElement type)
{
	cellule_t* cel = nouvelleCellule();

	cel->val = val;
	cel->type = type;
	cel->suivant = seq->tete;
	seq->tete = cel;

}


void depiler (sequence_t * seq) {
	cellule_t* cel = seq->tete;
	seq->tete = seq->tete->suivant;
	detruireCellule (cel);
}


void conversion (char *texte, sequence_t *seq)
{
	seq->tete = NULL;
	cellule_t* cel;
	cellule_t* mem = nouvelleCellule();
	int i = 0;
	
	while (texte[i] != '\0') {

		if (texte[i] != ' '
			|| texte[i] != '\t'
			|| texte[i] != '\n'
			|| texte[i] != '\r') 
		{
			cel = nouvelleCellule();
			cel->val.c = texte[i];
			cel->type = CHAR;

			// Cas première cellule
			if (seq->tete == NULL) { seq->tete = cel; }

			else {
				mem->suivant = cel;
				cel->precedent = mem;
			}

			mem = cel;
		}

		i++;
	}
}


void afficher (sequence_t* seq)
{
    assert (seq);
	cellule_t* cursor = seq->tete;
	while (cursor != NULL) {
		if (cursor->type == CHAR) {
			printf ("%c", cursor->val.c);
		}
		else if (cursor->type == INT) {
			printf ("%d", cursor->val.i);
		}
		else if (cursor->type == SEQ) {
			printf(" SEQ ");
		}
		cursor = cursor->suivant;
	}
	printf("\n");
}


void operation (sequence_t* seq, cellule_t* cel)
{
	cellule_t* cel1 = cel->precedent;
	cellule_t* cel2 = cel1->precedent;
	
	switch (cel->val.c) {
		case '+':
			cel2->val.i = cel1->val.i + cel2->val.i;
			break;
		case '-':
			cel2->val.i = cel1->val.i - cel2->val.i;
			break;
		case '*':
			cel2->val.i = cel1->val.i * cel2->val.i;
			break;
	}

	empiler (seq, cel2->val, cel2->type);

	detruireCellule (cel1);
}
