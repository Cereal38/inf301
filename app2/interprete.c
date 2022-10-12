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

	testAll();
	
    //debug = true; /* À enlever par la suite et utiliser "-d" sur la ligne de commandes */
	
	// Variables
	cellule_t* cel = nouvelleCellule();
	cel = seq->tete;

	
    printf ("Programme:");
    afficher(seq);
    printf ("\n");
    if (debug) stop();

    int ret;

    while ( cel != NULL ) {

		printf ("Commande: %c\n", cel->command);

        switch (cel->command) {

            case 'A':
                ret = avance();
                if (ret == VICTOIRE) return VICTOIRE; /* on a atteint la cible */
                if (ret == RATE)     return RATE;     /* tombé dans l'eau ou sur un rocher */
                break; /* à ne jamais oublier !!! */

			case 'D':
				droite();
				break;

			case 'G':
				gauche();
				break;

            default:
                eprintf("Caractère inconnu: '%c'\n", cel->command);
        }
		
		// Prochaine commande
		cel = cel->suivant;

        /* Affichage pour faciliter le debug */
        afficherCarte();
        printf ("Programme:");
        afficher(seq);
        printf ("\n");
        if (debug) stop();

    }

    /* Si on sort de la boucle sans arriver sur la cible,
     * c'est raté :-( */

    return CIBLERATEE;
}
