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

/**
 * @brief Initialise le serpent.
 * 
 * @param nb_lignes 
 * @param nb_colonnes 
 * @param taille 
 * @return Serpent 
 */
Serpent serpent_initialiser(int nb_lignes, int nb_colonnes, int taille);

/**
 * @brief Retourne la case devant la tête du serpent.
 * 
 * @param serp 
 * @return Case 
 */
Case serpent_case_visee(Serpent serp);

/**
 * @brief Ajoute une case au serpent.
 * 
 * @param serpent 
 * @param c 
 */
void serpent_ajoute_case(ListeSerpent* serpent, Case c);

/**
 * @brief Alloue une case pour le serpent.
 * 
 * @param nb_lignes 
 * @param nb_colonnes 
 * @param taille 
 * @return Serpent 
 */
ListeSerpentEntry* alloue_case_serpent(Case c);

#endif
