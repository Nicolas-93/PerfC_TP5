#include "serpent.h"
#include "case.h"
#include <stdlib.h>


Serpent serpent_initialiser(int nb_lignes, int nb_colonnes, int taille) {
    Serpent snake;
    
    for (int i = 0; i < taille; ++i) {
        Case c = {
            .x = nb_colonnes / 2, .y = nb_lignes / 2
        };

        serpent_ajoute_case(&snake.snake_cases, c);
    }

    snake.len_snake = taille;
    
    return snake;
}

void serpent_ajoute_case(ListeSerpent* serpent, Case c) {
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

    switch (serp.snake_dir) {
    case UP:
        c.x += 1;
        break;
    case DOWN:
        c.y -= 1;
        break;
    case LEFT:
        c.x -= 1;
        break;
    case RIGHT:
        c.y += 1;
        break;
    default:
        break;
    }

    return c;
}
