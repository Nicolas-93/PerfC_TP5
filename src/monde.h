#ifndef MONDE_INCLUDED
#define MONDE_INCLUDED

#include "pomme.h"
#include <stdbool.h>

typedef struct monde {
    int hauteur, largeur;
    Serpent snake;
    int eaten_apples;
    ListePommes apples;
} Monde;

/**
 * @brief Ajoute une pomme au monde.
 * 
 * @param mon 
 */
void monde_ajouter_pomme(Monde *mon);

/**
 * @brief Initialise le monde.
 * 
 * @param nb_lignes 
 * @param nb_colonnes 
 * @param taille_serpent 
 * @param nb_pommes 
 * @return Monde 
 */
Monde monde_initialiser(
    int nb_lignes, int nb_colonnes,
    int taille_serpent, int nb_pommes
);

/**
 * @brief Retourne vrai si le serpent est mort.
 * 
 * @param monde 
 * @return int 
 */
int monde_est_mort_serpent(Monde monde);

/**
 * @brief Avance le serpent.
 * 
 * @param mon 
 */
void monde_evoluer_serpent(Monde* mon);

/**
 * @brief Retourne vrai si une pomme existe en case
 * ``c``.
 * 
 * @param apples 
 * @param c 
 * @return true 
 * @return false 
 */
bool monde_pomme_existe(ListePommes apples, Case c);

/**
 * @brief Retourne vrai si le corps du serpent
 * existe en case ``c``.
 * 
 * @param snake 
 * @param c 
 * @return true 
 * @return false 
 */
bool monde_serpent_existe(ListeSerpent snake, Case c);

#endif
