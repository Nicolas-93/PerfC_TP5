#ifndef POMME_INCLUDED
#define POMME_INCLUDED
#include "case.h"

typedef struct pomme {
    Case c;
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

/**
 * @brief Supprime la pomme en position ``c`` de la liste des pommes.
 * 
 * @param pommes 
 * @param c 
 * @return int 1 si la pomme a été supprimée, 0 si la pomme
 * n'existait pas.
 */
int pomme_liste_supprime_pomme(ListePommes* pommes, Case c);

#endif
