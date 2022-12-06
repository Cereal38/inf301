#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"

/* fichier à compléter au besoin */

void init_liste_vide(liste_t* L) {
   L->tete = NULL;
}

void liberer_liste(liste_t* L) {
	
	struct cellule * parcours = (struct cellule*) malloc (sizeof(struct cellule)); 

	parcours = L->tete;

	while (parcours != NULL) {
		L->tete = parcours->suivant;
		free(parcours);
		parcours = L->tete;
	}

}


int ajouter_tete(liste_t* L, string c) { /* retourne 0 si OK, 1 sinon  */

	struct cellule * new = (struct cellule*) malloc (sizeof(struct cellule)); 

	// Erreur malloc
	if (new == NULL) {
		return 1;
	}

	new->val = strdup(c);

	// Liste vide
	if (L->tete == NULL) {
		L->tete = new;
		return 0;
	}

	new->suivant = L->tete;
	L->tete = new;
	return 0;
}


