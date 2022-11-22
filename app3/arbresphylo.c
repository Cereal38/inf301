#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"


void analyse_arbre_rec (arbre racine, int* nb_esp, int* nb_carac)
{

	if (racine == NULL) { return; }

	// Cas d'une feuille (espèce)
	if (racine->gauche == NULL && racine->droit == NULL) {
		(*nb_esp)++;
		return;
	}

	// Cas d'un noeud (caractéristique)
	(*nb_carac)++;

	analyse_arbre_rec(racine->gauche, nb_esp, nb_carac);
	analyse_arbre_rec(racine->droit, nb_esp, nb_carac);

}

void analyse_arbre (arbre racine, int* nb_esp, int* nb_carac)
{

	(*nb_esp) = 0;
	(*nb_carac) = 0;
	analyse_arbre_rec(racine, nb_esp, nb_carac);

}


/* ACTE II */
/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y mettre les
 * caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece (arbre racine, char *espece, liste_t* seq)
{

	if (racine == NULL) { return 1; }

	if (strcmp(racine->valeur, espece) == 0) {
		return 0;
	}

	int gauche = 1;
	int droite = 1;

	if (racine->gauche != NULL) {
		gauche = rechercher_espece(racine->gauche, espece, seq);
	}

	if (racine->droit != NULL) {
		droite = rechercher_espece(racine->droit, espece, seq);
		if (droite == 0) {
			ajouter_tete(seq, racine->valeur);
		}
	}


	return (droite * gauche);
}



/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un 
 * message d'erreur.
 */
int ajouter_espece (arbre* a, char *espece, cellule_t* seq) {

	cellule_t * parcours = (cellule_t *) malloc(sizeof(cellule_t));
	noeud * tempArbre = (noeud *) malloc(sizeof(noeud));
	parcours = seq;

	while (tempArbre != NULL) {

		if (parcours != NULL) { 
		
			if (strcmp(tempArbre->valeur, parcours->val) == 0) {
				tempArbre = tempArbre->droit;
				parcours = parcours->suivant;
			}
			else {
				tempArbre = tempArbre->gauche;
			}

		} else {
			tempArbre = tempArbre->gauche;
		}

	}

	noeud * new = (noeud *) malloc (sizeof(noeud));
	new->valeur = strdup(espece);

	tempArbre = new;

    return 0;
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau (arbre racine, FILE* fout) {
   printf ("<<<<< À faire: fonction afficher_par_niveau fichier " __FILE__ "\n >>>>>");
}

// Acte 4


int ajouter_carac(arbre* a, char* carac, cellule_t* seq) {
   printf ("<<<<< À faire: fonction ajouter_carac fichier " __FILE__ "\n >>>>>");
   return 0;
}

