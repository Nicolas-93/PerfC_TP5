#include "monde.h"
#include <stdlib.h>
#include <stdbool.h>
#include "pomme.h"
#include "serpent.h"

void monde_ajouter_pomme(Monde *mon) {

    Pomme apple;

    do {
        apple = pomme_aleatoire(mon->hauteur, mon->largeur);
    } while (
        monde_pomme_existe(mon->apples, apple.apple_case)
        || monde_serpent_existe(mon->snake.snake_cases, apple.apple_case));

    ListePommesEntry* entry = alloue_pomme(apple);
    
    entry->next = mon->apples;
    mon->apples = entry;
}

bool monde_pomme_existe(ListePommes apples, Case c) {

    for ( ; apples; apples = &((apples)->next)) {
        
        if (apples->p.apple_case.x == c.x
            && apples->p.apple_case.y == c.y)
            return true;
    }
    return false;
}

bool monde_serpent_existe(ListeSerpent snake, Case c) {

    for ( ; snake; snake = &((snake)->next)) {
        
        if (snake->c.x == c.x && snake->c.y == c.y)
            return true;
    }
    return false;
}

Monde monde_initialiser(int nb_lignes, int nb_colonnes, int taille_serpent, int nb_pommes) {
    Monde monde = {
        .largeur = nb_colonnes,
        .hauteur = nb_lignes,
        .snake = (Serpent) {
            .len_snake = taille_serpent,
            .snake_dir = RIGHT,
        },
        .eaten_apples = 0,
    };

    monde.snake = serpent_initialiser(nb_lignes, nb_colonnes, taille_serpent);
    
    for (int i = 0; i < taille_serpent; ++i)
        monde_ajouter_pomme(&monde);
    
    return monde;
}

int monde_est_mort_serpent(Monde monde) {
    Case new_case = serpent_case_visee(monde.snake);
    if (new_case.x <= 0 || new_case.y <= 0 || 
        new_case.x >= monde.largeur || new_case.y >= monde.hauteur)
        return true;

    if (monde_serpent_existe(monde.snake.snake_cases, new_case))
        return true;

    return false;
}

void monde_evoluer_serpent(Monde* monde) {
    if (monde_est_mort_serpent(*monde)) {
        return;
    }
    Case new_tete = serpent_case_visee(monde->snake);
    if (monde_pomme_existe(monde->apples, new_tete )) {
        pomme_liste_supprimer_pomme(monde);
        monde->eaten_apples++;
        monde_ajouter_pomme(monde);
    }

}