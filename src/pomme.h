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


/**
 * @brief Alloue une pomme.
 * 
 * @param p 
 * @return ListePommesEntry* 
 */
ListePommesEntry* alloue_pomme(Pomme p);

/**
 * @brief Retourne une pomme aléatoire.
 * 
 * @param nb_lignes 
 * @param nb_colonnes 
 * @return Pomme 
 */
Pomme pomme_aleatoire(int nb_lignes, int nb_colonnes);

/**
 * @brief Ajoute une pomme à la liste de pommes.
 * 
 * @param pommes 
 * @param p 
 * @return int 
 */
int pomme_ajoute_pomme(ListePommes* pommes, Pomme p);

#endif
