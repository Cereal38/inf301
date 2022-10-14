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
	pile_t * pile = nouvellePile();
    int ret;
	sequence_t * bloc;
	int ternaire;
	sequence_t * seqVrai;
	sequence_t * seqFaux;
	

    printf ("Programme:");
    afficher(seq);
    printf ("\n");
    if (debug) stop();

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

			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				empiler(pile, (valeurPile) convertCharToInt(cel->command), INT);
				break;

			case '+':
				additionner(pile);
				break;

			case '-':
				soustraire(pile);
				break;

			case '*':
				multiplier(pile);
				break;

			case 'P':
				pose(depiler(pile)->valeur.i);
				break;

			case 'M':
				empiler(pile, (valeurPile) mesure(depiler(pile)->valeur.i), INT);
				break;
			
			case '{':

				// Créé la nouvelle séquence qui va être empilée
				bloc = nouvelleSequence();

				// N'ajoute pas l'acolade à la séquence
				cel = cel->suivant;

				// Ajoute les commandes de la séquence au bloc
				while (cel->command != '}') {
					ajouterEnQueue(bloc, cel->command);
					cel = cel->suivant;
				}

				// Ajoute le bloc à la pile
				empiler(pile, (valeurPile) bloc, BLOC);

				break;

			case '?':

				// Récupère les 2 séquences et le ternaire
				seqVrai = (sequence_t *) depiler(pile)->valeur.s;
				seqFaux = (sequence_t *) depiler(pile)->valeur.s;
				ternaire = depiler(pile)->valeur.i;

				// Exécute la bonne séquence
				if (ternaire == 0) { interprete(seqVrai, debug); }
				else { interprete(seqFaux, debug); }

				break;

            default:
                eprintf("Caractère inconnu: '%c'\n", cel->command);
        }

		// Affichage pile
		printf("Pile: ");
		afficherPile(pile);
		
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
