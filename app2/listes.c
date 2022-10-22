#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
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

	// Cas où la pile est vide
	if (pile->tete == NULL) {
		printf ("Nil\n");
		return;
	}

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


void inverseDeuxPremiers (pile_t * pile) {
	element_t * cel1 = (element_t*) malloc (sizeof (element_t));
	element_t * cel2 = (element_t*) malloc (sizeof (element_t));
	cel1 = depiler (pile);
	cel2 = depiler (pile);
	empiler(pile, cel1->valeur, cel1->type);
	empiler(pile, cel2->valeur, cel2->type);
}


void clonerPremier (pile_t * pile) {

	// Cas de la pile vide
	if (pile->tete == NULL) { return; }

	cellule_t * cel;
	sequence_t * seqClone;

	switch (pile->tete->type) {
		case INT:
			empiler(pile, pile->tete->valeur, INT);
			break;
		case CHAR:
			empiler(pile, (valeurPile) pile->tete->valeur.c, CHAR);
			break;
		case BLOC:
			cel = (cellule_t*) malloc (sizeof (cellule_t));
			cel = pile->tete->valeur.s->tete;
			seqClone = nouvelleSequence();
			while (cel != NULL) {
				ajouterEnQueue(seqClone, cel->command);
				cel = cel->suivant;
			}
			empiler(pile, (valeurPile) seqClone, BLOC);
			break;
	}

}


void decaleGauche (pile_t * pile, int n) {

	// Variable
	int i;
	element_t * mem;
	element_t * parcours;

	// Cas où n vaut 0 ou 1
	if (n == 0 || n == 1) { return; }

	// Cas où n vaut 2
	if (n == 2) {
		inverseDeuxPremiers(pile);
		return;
	}

	// On parcours la pile pour récupérer le n-ième élément
	parcours = pile->tete;
	for (i = 0; i < n-2; i++) {
		parcours = parcours->suivant;
	}
	mem = parcours->suivant;
	parcours->suivant = mem->suivant;
	mem->suivant = pile->tete;
	pile->tete = mem;
	
}


int convertCharToInt (char c)
{
	return c - '0';
}
// --- End piles --- //


// --- Start others --- //
void interpreteSequence(sequence_t * seq, int * ret, pile_t * pile) {

	// --- Start variables --- //
	
	// Générales
	int i;

	cellule_t* cel = nouvelleCellule();
	cel = seq->tete;
	sequence_t * bloc;
	int compteAccolades;
	sequence_t * seqTemp;
	element_t * elemTemp;
	int bCount;

	// Case ?
	int ternaire;
	sequence_t * seqVrai;
	sequence_t * seqFaux;

	// Case R
	int nR;
	int xR;

	// --- End variables --- //

	// Affiche la séquence
	printf ("Programme:");
	afficher(seq);
	printf ("\n");

	while ( cel != NULL && *ret != VICTOIRE  ) {

		// Affichage (Sauf si le caractère est un espace ou LF)
		if (cel->command != ' ' && cel->command != '\n') {
			printf("Pile: ");
			afficherPile(pile);
			printf ("Commande: %c\n", cel->command); 
		}

        switch (cel->command) {

            case 'A':
                *ret = avance();
                break;

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

			case 'X':
				inverseDeuxPremiers(pile);
				break;

			case 'B':
				bCount = depiler(pile)->valeur.i;
				while (bCount > 0) {
					interpreteSequence(pile->tete->valeur.s, ret, pile);
					bCount--;
				}
				break;

			case '!':
				// Cas de la pile vide
				if (pile->tete == NULL) { break; }

				// Transforme le premier élément en sequence pour
				// l'exécuter avec interpreteSequence()
				seqTemp = nouvelleSequence();
				elemTemp = (element_t*) malloc (sizeof (element_t));
				elemTemp = depiler(pile);

				switch (elemTemp->type) {
					case CHAR:
						ajouterEnTete(seqTemp, (char) elemTemp->valeur.c);
						break;
					case BLOC:
						seqTemp = elemTemp->valeur.s;
						break;
					case INT:
						printf("Erreur : Impossible d'exécuter un entier\n");
						break;
				}

				interpreteSequence(seqTemp, ret, pile);
				free(seqTemp);
				free(elemTemp);
				break;

			case 'C':
				clonerPremier(pile);
				break;

			case 'R' :
				xR = depiler(pile)->valeur.i;
				nR = depiler(pile)->valeur.i;
				for (i = 0; i < xR; i++) {
					decaleGauche(pile, nR);
				}
				break;

			case 'I' :
				depiler(pile);
				break;
			
			case '{':

				compteAccolades = 0;

				// Créé la nouvelle séquence qui va être empilée
				bloc = nouvelleSequence();

				// N'ajoute pas l'acolade à la séquence
				cel = cel->suivant;

				// Ajoute les commandes de la séquence au bloc
				while (cel->command != '}' || compteAccolades != 0) {
					
					// Si on rencontre une accolade, on incrémente / décremente le compteur
					if (cel->command == '{') { compteAccolades++; }
					if (cel->command == '}') { compteAccolades--; }

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
				if (ternaire == 0) { interpreteSequence(seqVrai, &(*ret), pile); }
				else { interpreteSequence(seqFaux, &(*ret), pile); }

				break;

			case ' ':
			case '\n':
				break;

            default:
                eprintf("Caractère inconnu: '%d'\n", cel->command);
        }

		// Prochaine commande
		cel = cel->suivant;

    }

}
// --- End others --- //
