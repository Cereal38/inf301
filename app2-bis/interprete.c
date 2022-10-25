#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"


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

	// Variables
	int ret;
	cellule_t* cursor = nouvelleCellule();
	cursor = seq->tete;

    debug = false;

    printf ("Programme:");
    //afficher(seq);
    printf ("\n");

    if (debug) stop();

    while ( cursor != NULL ) {

        switch (cursor->type) {

			case CHAR:
					
				// Affiche la commande
				printf("Commande: %c\n", cursor->val.c);

				switch (cursor->val.c) {

					case 'A':

						ret = avance();
						if (ret == VICTOIRE) return VICTOIRE;
						if (ret == RATE)     return RATE; 
						break; 

					case 'D':

						droite();
						break;

					case 'G':

						gauche();
						break;

					case '+':
						
						operation(seq, cursor);
						break;

					case '-':
						
						operation(seq, cursor);
						break;

					case '*':
						
						operation(seq, cursor);
						break;

					default:
						eprintf("Caractère inconnu: '%c'\n", cursor->val.c);
				}
				depiler(seq);
				break;

			default:
				eprintf("ERREUR TYPE !\n");
		}

		cursor = cursor->suivant;

		/*
        // Affichage pour faciliter le debug
        afficherCarte();
        printf ("Programme:");
        afficher(seq);
        printf ("\n");
        if (debug) stop();
		*/
    }

    /* Si on sort de la boucle sans arriver sur la cible,
     * c'est raté :-( */

    return CIBLERATEE;
}
