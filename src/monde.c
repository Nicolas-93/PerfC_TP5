#include "monde.h"
#include "pomme.h"
#include "types.h"
#include "list.h"
#include "serpent.h"
#include <stdlib.h>
#include <stdbool.h>

void monde_ajouter_pomme(Monde *mon) {

    Pomme apple;

    do {
        apple = pomme_aleatoire(mon->hauteur, mon->largeur);
    } while (
        monde_pomme_existe(&mon->apples, apple.c) ||
        monde_serpent_existe(&mon->snake.snake_cases, apple.c)
    );

    pomme_ajoute_pomme(&mon->apples, apple);
}

bool monde_pomme_existe(const ListePommes* apples, Case c) {
    ListePommesEntry* entry;
    LIST_FOREACH(entry, apples) {
        if (entry->p.c.x == c.x && entry->p.c.y == c.y)
            return true;
    }
    return false;
}

bool monde_serpent_existe(const ListeSerpent* snake, Case c) {
    ListeSerpentEntry* entry;
    LIST_FOREACH(entry, snake) {
        if (entry->c.x == c.x && entry->c.y == c.y)
            return true;
    }
    return false;
}

Monde monde_initialiser(
    int nb_lignes, int nb_colonnes,
    int taille_serpent, int nb_pommes
) {
    Monde monde = {
        .largeur = nb_colonnes,
        .hauteur = nb_lignes,
        .eaten_apples = 0,
        .pause = false,
    };

    monde.snake = serpent_initialiser(nb_lignes, nb_colonnes, taille_serpent);

    LIST_INIT(&monde.apples);
    for (int i = 0; i < taille_serpent; ++i)
        monde_ajouter_pomme(&monde);

    return monde;
}

int monde_est_mort_serpent(Monde monde) {
    Case new_case = serpent_case_visee(&monde.snake);
    if (new_case.x < 0 || new_case.y < 0 || 
        new_case.x >= monde.largeur || new_case.y >= monde.hauteur)
        return true;

    if (monde_serpent_existe(&monde.snake.snake_cases, new_case))
        return true;

    return false;
}

int monde_evoluer_serpent(Monde* monde) {
    if (monde_est_mort_serpent(*monde)) {
        return SERPENT_MORT;
    }
    Case new_tete = serpent_case_visee(&monde->snake);
    if (monde_pomme_existe(&monde->apples, new_tete)) {
        pomme_liste_supprime_pomme(&monde->apples, new_tete);
        monde_ajouter_pomme(monde);
        serpent_ajoute_case(&monde->snake.snake_cases, new_tete);
        monde->eaten_apples++;
    }
    if (!serpent_avancer(&monde->snake))
        return 0;

    return MONDE_NONE;
}
