#ifndef SERPENT_INCLUDED
#define SERPENT_INCLUDED

#include "case.h"


typedef struct _ListeSerpent {
    Case c;
    struct _ListeSerpent* next;
} ListeSerpentEntry, *ListeSerpent;

typedef struct serpent
{
    Direction snake_dir;
    ListeSerpent snake_cases;
    int len_snake;
} Serpent;

Serpent serpent_initialiser(int nb_lignes, int nb_colonnes, int taille);
Case serpent_case_visee(Serpent serp);
ListeSerpentEntry* alloue_case_serpent(Case c);


#endif
