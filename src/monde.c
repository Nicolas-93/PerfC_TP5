#include "monde.h"
#include "pomme.h"
#include "types.h"
#include "list.h"
#include "serpent.h"
#include "random.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

void monde_ajouter_pomme(Monde *mon, PommeType type) {
    Pomme apple;

    do {
        apple = pomme_aleatoire(mon->hauteur, mon->largeur);
    } while (
        monde_pomme_existe(&mon->apples, apple.c) ||
        monde_serpent_existe(&mon->snake.snake_cases, apple.c)
    );

    if (type == (POMME_DOUBLE | POMME_NORMALE))
        apple.type = random_bool() ? POMME_DOUBLE : POMME_NORMALE; 
    else
        apple.type = type;

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
    int taille_serpent, int nb_pommes, int pourcent_empoisonne
) {
    assert(pourcent_empoisonne >= 0 && pourcent_empoisonne <= 100);
    Monde monde = {
        .largeur = nb_colonnes,
        .hauteur = nb_lignes,
        .eaten_apples = 0,
        .pause = false,
        .nb_pommes = nb_pommes,
        
        .params = {
            .sound = true,
            .duree_tour = 250,
            .pourcentage_empoisonnees = pourcent_empoisonne,
        },

        .snake = {
            .len = taille_serpent,
        }
    };
    
    monde_initialiser_aux(&monde);

    return monde;
}

void monde_initialiser_aux(Monde* monde) {
    monde->snake = serpent_initialiser(monde->hauteur, monde->largeur, monde->snake.len);

    monde->nb_pommes_empoisonnees = ((float) monde->params.pourcentage_empoisonnees / 100) * monde->nb_pommes;

    LIST_INIT(&monde->apples);
    PommeType est_empoisonnee;
    for (int i = 0; i < monde->nb_pommes; ++i) {
        est_empoisonnee = i < monde->nb_pommes_empoisonnees ? POMME_EMPOISOINNE : POMME_NORMALE;
        monde_ajouter_pomme(monde, est_empoisonnee);
    }
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
        Pomme deleted = pomme_liste_supprime_pomme(&monde->apples, new_tete);
        
        switch (deleted.type) {
        case POMME_EMPOISOINNE:
            return SERPENT_MORT;
        case POMME_DOUBLE:
            monde->score += 2;
            break;
        case POMME_NORMALE:
            monde->score++;
        default:
            break;
        }

        monde_ajouter_pomme(monde, POMME_NORMALE | POMME_DOUBLE);
        serpent_ajoute_case(&monde->snake.snake_cases, new_tete);
        monde->eaten_apples++;
    }
    if (!serpent_avancer(&monde->snake))
        return 0;

    return MONDE_NONE;
}
