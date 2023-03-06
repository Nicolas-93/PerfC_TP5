#ifndef POMME_INCLUDED
#define POMME_INCLUDED
#include "case.h"

typedef struct pomme {
    Case apple_case;
} Pomme;

typedef struct _ListePommes {
    Pomme p;
    struct _ListePommes *next;
} ListePommesEntry, *ListePommes;


Pomme pomme_aleatoire(int nb_lignes, int nb_colonnes);

#endif
