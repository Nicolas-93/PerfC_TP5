#ifndef MONDE_INCLUDED
#define MONDE_INCLUDED

#include "pomme.h"
#include "serpent.h"
#include <stdbool.h>
#include <ncurses.h>

typedef struct monde {

    int hauteur, largeur;
    int eaten_apples;
    int score;
    Serpent snake;
    ListePommes apples;
    bool pause;
    
    int nb_pommes;
    int nb_pommes_empoisonnees;
    
    struct {
        int sound;
        int duree_tour;
        int pourcentage_empoisonnees;
    } params;

} Monde;

typedef enum MondeErreur {
    MONDE_NONE,
} MondeErreur;

/**
 * @brief Ajoute une pomme au monde.
 * 
 * @param mon 
 * @param type type de pomme à ajouter
 */
void monde_ajouter_pomme(Monde *mon, PommeType type);

/**
 * @brief Initialise un monde avec une configuration
 * par défaut.
 * 
 * @param nb_lignes 
 * @param nb_colonnes 
 * @param taille_serpent 
 * @param nb_pommes 
 * @return Monde 
 */
Monde monde_initialiser(
    int nb_lignes, int nb_colonnes,
    int taille_serpent,
    int nb_pommes, int pourcent_empoisonne
);

/**
 * @brief Initialise les composants du monde
 * (liste de pommes, cases du serpent)
 * 
 * @param monde 
 * @return int 
 */
void monde_initialiser_aux(Monde* monde);

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
 * @return int -1 si le serpent est mort, 0 si une
 * erreur d'allocation de mémoire est survenue, 1 sinon.
 */
int monde_evoluer_serpent(Monde* mon);

/**
 * @brief Retourne vrai si une pomme existe en case
 * ``c``.
 * 
 * @param apples 
 * @param c 
 * @return true 
 * @return false 
 */
bool monde_pomme_existe(const ListePommes* apples, Case c);

/**
 * @brief Retourne vrai si le corps du serpent
 * existe en case ``c``.
 * 
 * @param snake 
 * @param c 
 * @return true 
 * @return false 
 */
bool monde_serpent_existe(const ListeSerpent* snake, Case c);

#endif
