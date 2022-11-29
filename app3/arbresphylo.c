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


/* ACTE 1b
 * Génére le fichier .dot correspondant à l'arbre phylogénétique
*/
void generer_dot_rec (arbre racine, FILE * fichier) {

	// On fait un parcours préfix de l'arbre et on écrit au fur et à mesure dans le fichier
	if (racine == NULL) { return; }

	// Cas d'une feuille (espèce)
	if (racine->gauche == NULL && racine->droit == NULL) {
		return;
	}

	// Cas d'un noeud (caractéristique)
	if (racine->gauche != NULL) {
		fprintf(fichier, "\t%s -> %s [fillcolor=red, fontcolor=red, shape=box, label = \"non\"];\n", racine->valeur, racine->gauche->valeur);
		generer_dot_rec(racine->gauche, fichier);
	}
	if (racine->droit != NULL) {
		fprintf(fichier, "\t%s -> %s [fillcolor=green, fontcolor=green, label = \"oui\"];\n", racine->valeur, racine->droit->valeur);
		generer_dot_rec(racine->droit, fichier);
	}

}

// afficher : 0 = ne pas afficher, 1 = afficher
int generer_dot (arbre racine, char * nomFichier, int afficher) {

	// On ouvre le fichier et on initialise le text
	FILE * fichier = fopen(nomFichier, "w");
	if (fichier == NULL) { return 1; }
	fprintf(fichier, "digraph arbre {\n");
	fprintf(fichier, "\tnode [shape=box];\n");

	// On appelle la fonction récursive
	generer_dot_rec(racine, fichier);

	// On ajoute la dernière ligne du fichier
	fprintf(fichier, "}");
	
	fclose(fichier);

	// Génère le svg de l'image, supprime le .dot et affiche l'image si demandé
	system("dot -Tsvg arbre.dot -o arbre.svg");
	system("rm arbre.dot");
	system("firefox arbre.svg");

	return 0;

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



// Acte 3
/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un 
 * message d'erreur.
 */
int ajouter_espece (arbre* a, char *espece, cellule_t* seq) {

	// L'arbre est vide et il n'y a plus de caractéristiques à ajouter
	if ((*a) == NULL && seq == NULL) {
		printf("L'arbre est vide et il n'y a plus de caractéristiques à ajouter.\n");
		(*a) = (arbre) malloc (sizeof(noeud));
		(*a)->valeur = strdup(espece);
		(*a)->gauche = NULL;
		(*a)->droit = NULL;
		printf("L'espèce %s a bien été ajoutée.\n\n", (*a)->valeur);
		return 0;
	}

	// L'arbre est vide et il reste des caractéristiques à ajouter
	if ((*a) == NULL && seq != NULL) {
		printf("L'arbre est vide et il reste des caractéristiques à ajouter.\n");
		(*a) = (arbre) malloc (sizeof(noeud));
		(*a)->valeur = strdup(seq->val);
		(*a)->gauche = NULL;
		(*a)->droit = NULL;
		printf("La caractéristique %s a bien été ajoutée.\n", (*a)->valeur);
		return ajouter_espece(&(*a)->gauche, espece, seq->suivant);
	}

	// L'arbre n'est pas vide et la caractéristique est en tête de la séquence
	if (strcmp(seq->val, (*a)->valeur) == 0) {
		printf("L'arbre n'est pas vide et la caractéristique est en tête de la séquence.\n");
		ajouter_espece(&((*a)->droit), espece, seq->suivant);
	}

	// L'arbre n'est pas vide et la caractéristique n'est pas en tête de séquence
	else {
		printf("L'arbre n'est pas vide et la caractéristique n'est pas en tête de séquence.\n");
		ajouter_espece(&((*a)->gauche), espece, seq);
	}

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

