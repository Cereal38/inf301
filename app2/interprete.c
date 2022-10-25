#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"
#include "asserts.h"


/*
 *  Auteur(s) :
 *  Date :
 *  Suivi des Modifications :
 *
 */

void stop (void)
{
    char enter = '\0';
    printf ("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
}



int interprete (sequence_t* seq, bool debug)
{

	// TEST - TO REMOVE
	testAll();

	// Variables
	int ret;
	pile_t * pile = nouvellePile();

	interpreteSequence(seq, &ret, pile);

	if (ret == VICTOIRE || ret == RATE) { return ret; }
	else { return CIBLERATEE; }
}
