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

typedef struct sequence sequence_t;

typedef enum typeElement {INT, CHAR, SEQ} typeElement;

typedef union {
	int i;
	char c;
	sequence_t *s;
} valeurPile;
			  
struct cellule {
	typeElement type;
	valeurPile val;
    struct cellule *precedent;
    struct cellule *suivant;
};
typedef struct cellule cellule_t;

struct sequence {
    cellule_t *tete;
};

cellule_t* nouvelleCellule (void);

void detruireCellule (cellule_t*);

void empiler (sequence_t* seq, valeurPile val, typeElement type);

void depiler (sequence_t * seq);

void conversion (char *texte, sequence_t *seq);

void afficher (sequence_t* seq);

void operation (sequence_t* seq, cellule_t* cel);


#endif
