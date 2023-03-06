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

void monde_ajouter_pomme(Monde *mon);
Monde monde_initialiser(
    int nb_lignes, int nb_colonnes,
    int taille_serpent, int nb_pommes
);
int monde_est_mort_serpent(Monde monde);
void monde_evoluer_serpent(Monde* mon);
bool monde_pomme_existe(ListePommes apples, Case c);

#endif
