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
struct element {
	int val;
	struct element *suivant;
};
typedef struct element element_t;

struct pile {
	element_t *tete;
};
typedef struct pile pile_t;

pile_t* nouvellePile(void);

void empiler (pile_t * pile, int val);

int depiler (pile_t * pile);

void additionner (pile_t * pile);

void soustraire (pile_t * pile);

void multiplier (pile_t * pile);

void afficherPile (pile_t * pile);

int convertCharToInt (char c);
// --- End piles --- //


#endif
