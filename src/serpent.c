#include "serpent.h"
#include "types.h"
#include "list.h"
#include <stdlib.h>


Serpent serpent_initialiser(int nb_lignes, int nb_colonnes, int taille) {
    Serpent snake = {
        .len = taille,
        .dir = RIGHT,
    };
    Case c = {
        .x = nb_colonnes / 2, .y = nb_lignes / 2,
    };
    LIST_INIT(&snake.snake_cases);
    
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

    LIST_INSERT_HEAD(serpent, entry);

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

Case serpent_case_visee(const Serpent* serp) {
    Case c = {0};
    Case tete = LIST_FIRST(&serp->snake_cases)->c ;
    c = tete;

    switch (serp->dir) {
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
    Case c = serpent_case_visee(serp);
     if (!serpent_ajoute_case(&serp->snake_cases, c))
        return 0;

    serpent_supprime_queue(serp);

    return 1;
}

void serpent_supprime_queue(Serpent* serp) {
    ListeSerpentEntry* entry = LIST_FIRST(&serp->snake_cases);
    ListeSerpentEntry* prev = NULL;

    while (entry->next) {
        prev = entry;
        entry = entry->next;
    }

    if (prev)
        prev->next = NULL;
    else
        LIST_FIRST(&serp->snake_cases) = NULL;

    free(entry);
}
