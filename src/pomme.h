#ifndef POMME_INCLUDED
#define POMME_INCLUDED
#include "types.h"
#include <stdbool.h>

typedef struct pomme {
    Case c;
    bool est_empoisonnee;
} Pomme;

typedef struct ListePommesEntry {
    Pomme p;
    struct ListePommesEntry *next;
} ListePommesEntry;

typedef struct ListePommes {
    ListePommesEntry* first;
    ListePommesEntry* last;
} ListePommes;

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
 * @brief Supprime la pomme en position ``c`` de la liste des pommes,
 * la renvoie.
 * 
 * @param pommes 
 * @param c 
 * @return Pomme supprimée
 */
Pomme pomme_liste_supprime_pomme(ListePommes* pommes, Case c);

#endif
