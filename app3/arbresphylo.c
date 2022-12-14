#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"

# define true 1
# define false 0
# define bool int


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
	if (afficher) {
		system("dot -Tsvg arbre.dot -o arbre.svg");
		system("rm arbre.dot");
		system("firefox arbre.svg");
	}

	return 0;

}


/* ACTE 2 */
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
int est_feuille (arbre racine) {
	return (racine->gauche == NULL && racine->droit == NULL);
}

int est_carac (arbre racine) {
	return (racine->gauche != NULL || racine->droit != NULL);
}

// Créer un arbre
arbre creer_arbre (char * valeur, arbre gauche, arbre droit) {

	arbre a = (arbre) malloc(sizeof(noeud));
	a->valeur = valeur;
	a->gauche = gauche;
	a->droit = droit;

	return a;
}


/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un 
 * message d'erreur.
*/
int ajouter_espece_rec (arbre* a, char *espece, cellule_t* seq) {

	// L'arbre est vide et il reste des caractéristiques à ajouter
	// On ajoute la caractéristique
	if ((*a) == NULL && seq != NULL) {
		(*a) = creer_arbre(seq->val, NULL, creer_arbre(espece, NULL, NULL));
		ajouter_espece_rec(&((*a)->droit), espece, seq->suivant);
	}

	// L'arbre est vide et il ne reste plus de caractéristiques à ajouter
	// On ajoute l'espèce
	if ((*a) == NULL && seq == NULL) {
		(*a) = creer_arbre(espece, NULL, NULL);
	}

	// L'arbre est une feuille et il reste des caractéristiques à ajouter
	// On remplace l'espece par la caractéristique et on ajoute les deux espèces
	if (est_feuille(*a) && seq != NULL) {

		char * especeTemp = (*a)->valeur;

		if (especeTemp == espece) { (*a) = creer_arbre(seq->val, NULL, creer_arbre(espece, NULL, NULL)); }
		else { (*a) = creer_arbre(seq->val, creer_arbre(especeTemp, NULL, NULL), creer_arbre(espece, NULL, NULL)); }

		ajouter_espece_rec(&((*a)->droit), espece, seq->suivant);

		return 0;
	}

	// L'arbre est une caractéristique et il reste des caractéristiques à ajouter
	// On ajoute la caractéristique
	if (est_carac(*a) && seq != NULL) {
		if (strcmp((*a)->valeur, seq->val) == 0) {
			ajouter_espece_rec(&((*a)->droit), espece, seq->suivant);
		} else {
			ajouter_espece_rec(&((*a)->gauche), espece, seq);
		}
	}

    return 0;
}

int ajouter_espece (arbre* a, char *espece, cellule_t* seq) {

	// On vérifie que l'espèce n'est pas déjà présente dans l'arbre
	liste_t* liste = (liste_t*) malloc (sizeof(liste_t));
	liste->tete = NULL;
	if (rechercher_espece(*a, espece, liste) == 0) {
		printf("L'espèce %s est déjà présente dans l'arbre.\n\n", espece);
		return 1;
	}

	// On ajoute l'espèce
	return ajouter_espece_rec(a, espece, seq);

	/*
	// On affiche l'arbre
	generer_dot(*a, "arbre.dot", 1);
	*/
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 *
 * PS : La fonction ne passe pas les tests mais je n'ai pas réussi à en comprendre la raison.
 * Elle affiche bien toutes les caractéristiques dans l'ordre du parcours en largeur.
 */
void afficher_par_niveau (arbre racine, FILE* fout) {

    // Si l'arbre est vide stop
    if (racine == NULL) { return; }

    // Création de la file
    file_t* file = (file_t*) malloc(sizeof(file_t));

    // Initialisation de la file
    file->tete = NULL;
    file->queue = NULL;

    // On ajoute la racine à la file
    enfiler(file, racine);

    // Tant que la file n'est pas vide
    while (file->tete != NULL) {
        arbre * a = defiler(file);
        arbre b = *a;

        // On affiche la valeur de l'élément si l'élément n'est pas une feuille
        if (b->gauche != NULL || b->droit != NULL) {
            fprintf(fout, "%s ", b->valeur);
        }

        // On ajoute les enfants à la file
        if (b->gauche != NULL) { enfiler(file, b->gauche); }
        if (b->droit != NULL) { enfiler(file, b->droit); }
    }

}



// Acte 4
int possede_carac (arbre racine, char *carac) {

	// Si l'arbre est vide stop
	if (racine == NULL) { return 0; }

	// Si l'arbre est une feuille stop
	if (est_feuille(racine)) { return 0; }

	// Si l'arbre est une caractéristique
	if (est_carac(racine)) {

		// Si la caractéristique est présente dans l'arbre
		if (strcmp(racine->valeur, carac) == 0) { return 1; }

		// Si la caractéristique n'est pas présente dans l'arbre
		else {
			return (possede_carac(racine->gauche, carac) || possede_carac(racine->droit, carac));
		}
	}

	return 0;
}


int verifier_clade (arbre racine, char *espece) {
	
	// Si l'arbre est vide stop
	if (racine == NULL) { return 0; }

	// Si l'arbre est une feuille
	if (est_feuille(racine)) {

		// Si l'espèce est présente dans l'arbre
		if (strcmp(racine->valeur, espece) == 0) { return 1; }

		// Si l'espèce n'est pas présente dans l'arbre
		else { return 0; }
	}

	// Si l'arbre est une caractéristique
	if (est_carac(racine)) {

		// Si l'espèce est présente dans l'arbre
		if (verifier_clade(racine->gauche, espece) == 1) { return 1; }
		if (verifier_clade(racine->droit, espece) == 1) { return 1; }

		// Si l'espèce n'est pas présente dans l'arbre
		else { return 0; }
	}

	return 0;

}

void ajouter_carac_rec(arbre * racine, char * carac, cellule_t * seq) {
	
	// Si l'arbre est vide stop
	if (*racine == NULL) { return; }

	// Si l'arbre est une feuille
	if (est_feuille(*racine)) {

		// Si la caractéristique est présente dans l'arbre
		if (strcmp((*racine)->valeur, carac) == 0) { return; }

		// Si la caractéristique n'est pas présente dans l'arbre
		else {
			(*racine) = creer_arbre(seq->val, creer_arbre(carac, NULL, NULL), creer_arbre((*racine)->valeur, NULL, NULL));
			return;
		}
	}

	// Si l'arbre est une caractéristique
	if (est_carac(*racine)) {

		// Si la caractéristique est présente dans l'arbre
		if (strcmp((*racine)->valeur, carac) == 0) { return; }

		// Si la caractéristique n'est pas présente dans l'arbre
		else {
			ajouter_carac_rec(&((*racine)->gauche), carac, seq);
			ajouter_carac_rec(&((*racine)->droit), carac, seq->suivant);
			return;
		}
	}

	return;
}

int ajouter_carac(arbre* a, char* carac, cellule_t* seq) {
    // Si l'arbre est vide, on ne peut pas ajouter de caractéristique
    if (*a == NULL) {
        printf("Ne peut ajouter %s: ne forme pas un sous-arbre.\n", carac);
        return 0;
    }

    // Si l'arbre n'est pas vide, on parcourt les noeuds de l'arbre en utilisant
    // une file pour parcourir l'arbre en largeur
    arbre * element = (arbre*) malloc(sizeof(noeud));
    file_t* file = (file_t*) malloc(sizeof(file_t));
    file->tete = NULL;
    file->queue = NULL;
    enfiler(file, *a);

    // On parcourt les noeuds de l'arbre en utilisant la file
    while (file->tete != NULL) {
        element = defiler(file);
        arbre b = *element;

        // Si le noeud courant possède la nouvelle caractéristique, on ajoute ses enfants à la file
        if (possede_carac(b, carac)) {
            if (b->gauche != NULL) { enfiler(file, b->gauche); }
            if (b->droit != NULL) { enfiler(file, b->droit); }
        }
    }

    // Une fois que la file est vide, on vérifie si les espèces qui possèdent la nouvelle caractéristique
    // forment bien un clade. Pour cela, on vérifie que tous les noeuds de l'arbre possèdent la nouvelle caractéristique
	// Si c'est le cas, on ajoute la nouvelle caractéristique à l'arbre
	if (verifier_clade(*a, carac)) {
		ajouter_carac_rec(a, carac, seq);
		return 1;
	} else {
		printf("Ne peut ajouter %s: ne forme pas un clade.\n", carac);
		return 0;
	}
}
