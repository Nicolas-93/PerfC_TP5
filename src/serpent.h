#ifndef SERPENT_INCLUDED
#define SERPENT_INCLUDED

#include "types.h"


typedef struct ListeSerpentEntry {
    Case c;
    struct ListeSerpentEntry* next;
} ListeSerpentEntry;

typedef struct ListeSerpent {
    ListeSerpentEntry* first;
    ListeSerpentEntry* last;
} ListeSerpent;


typedef struct serpent {
    Direction dir;
    ListeSerpent snake_cases;
    int len;
} Serpent;

typedef enum SerpentErreur {
    SERPENT_NONE,
    SERPENT_MORT = 1,
} SerpentErreur;

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
Case serpent_case_visee(const Serpent* serp);

/**
 * @brief Ajoute une case au serpent.
 * 
 * @param serpent 
 * @param c 
 * @return int 0 en cas d'erreur d'allocation, 1 sinon
 */
int serpent_ajoute_case(ListeSerpent* serpent, Case c);

/**
 * @brief Alloue une case pour le serpent.
 * 
 * @param nb_lignes 
 * @param nb_colonnes 
 * @param taille 
 * @return Serpent 
 */
ListeSerpentEntry* alloue_case_serpent(Case c);

/**
 * @brief Avance le serpent d'une case.
 * (Supprime la dernière case et ajoute
 * une case devant la tête)
 * @param serp 
 * @return int 
 */
int serpent_avancer(Serpent* serp);

/**
 * @brief Supprime la dernière case du serpent.
 * 
 */
void serpent_supprime_queue(Serpent* serp);

#endif
