#include "serpent.h"
#include "case.h"
#include <stdlib.h>


Serpent serpent_initialiser(int nb_lignes, int nb_colonnes, int taille) {
    Serpent snake = {
        .snake_cases = NULL,
        .len = taille,
        .dir = RIGHT,
    };
    Case c = {
        .x = nb_colonnes / 2, .y = nb_lignes / 2,
    };
    
    for (int i = 0; i < taille; ++i) {
        c.x += 1;
        serpent_ajoute_case(&snake.snake_cases, c);
    }
    snake.len = taille;

    return snake;
}

int serpent_ajoute_case(ListeSerpent* serpent, Case c) {
    ListeSerpentEntry* entry = alloue_case_serpent(c);

    if (!entry)
        return 0;

    entry->next = *serpent;
    *serpent = entry;

    return 1;
}

ListeSerpentEntry* alloue_case_serpent(Case c) {
    ListeSerpentEntry* snake = malloc(sizeof(ListeSerpentEntry));
    if (snake){
        snake->c = c;
        snake->next = NULL;
    }
    return snake;
}

Case serpent_case_visee(Serpent serp) {
    Case c = {0};
    Case tete = serp.snake_cases->c;
    c = tete;

    switch (serp.dir) {
    case UP:
        c.y -= 1;
        break;
    case DOWN:
        c.y += 1;
        break;
    case LEFT:
        c.x -= 1;
        break;
    case RIGHT:
        c.x += 1;
        break;
    default:
        break;
    }

    return c;
}

int serpent_avancer(Serpent* serp) {
    Case c = serpent_case_visee(*serp);
     if (!serpent_ajoute_case(&serp->snake_cases, c))
        return 0;

    serpent_supprime_queue(serp);

    return 1;
}

void serpent_supprime_queue(Serpent* serp) {
    ListeSerpentEntry* entry = serp->snake_cases;
    ListeSerpentEntry* prev = NULL;

    while (entry->next) {
        prev = entry;
        entry = entry->next;
    }

    if (prev)
        prev->next = NULL;
    else
        serp->snake_cases = NULL;

    free(entry);
}
