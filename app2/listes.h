#ifndef LISTES_H
#define LISTES_H

#include <stdbool.h>

/*
 * Pour réaliser des tests de performance, désactiver tous les 
 * affichages.
 * Pour cela, le plus simple est de redefinir les fonctions principales 
 * en decommentant les 3 lignes suivantes et en commentant l'ancienne 
 * definition de 'eprintf' juste dessous.
 */

#ifdef SILENT

#define printf(fmt, ...) (0)
#define eprintf(fmt, ...) (0)
#define putchar(c) (0)

#else

#define eprintf(...) fprintf (stderr, __VA_ARGS__)

#endif

extern bool silent_mode;


// --- Start sequences --- //
struct cellule {
    char   command;
    struct cellule *suivant;
};
typedef struct cellule cellule_t;

struct sequence {
    cellule_t *tete;
};
typedef struct sequence sequence_t;

sequence_t* nouvelleSequence(void);

cellule_t* nouvelleCellule (void);

void detruireCellule (cellule_t*);

void ajouterEnTete (sequence_t * liste, char val);

void ajouterEnQueue (sequence_t * liste, char val);

void conversion (char *texte, sequence_t *seq);

void afficher (sequence_t* seq);
// --- End sequences --- //


// --- Start piles --- //
typedef enum typeElement {INT, CHAR, BLOC} typeElement; // Type de l'élément de la pile
														
typedef union {
	int i;
	char c;
	sequence_t *s;
} valeurPile; // Valeur de l'élément de la pile
			  
struct element {
	struct element *suivant;
	typeElement type;
	valeurPile valeur;
};
typedef struct element element_t; // Element de la pile


struct pile {
	element_t *tete;
};
typedef struct pile pile_t; // Pile

pile_t* nouvellePile(void);

void empiler (pile_t * pile, valeurPile valeur, typeElement type);

element_t* depiler (pile_t * pile);

void additionner (pile_t * pile);

void soustraire (pile_t * pile);

void multiplier (pile_t * pile);

void afficherPile (pile_t * pile);

void inverseDeuxPremiers (pile_t * pile);

void clonerPremier (pile_t * pile);

int convertCharToInt (char c);
// --- End piles --- //


// --- Start others --- //
void interpreteSequence(sequence_t * seq, int * ret, pile_t * pile);
// --- End others --- //


#endif

