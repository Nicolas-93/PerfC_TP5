#include "pomme.h"
#include "types.h"
#include <stdlib.h>
#include "list.h"

Pomme pomme_aleatoire(int nb_lignes, int nb_colonnes) {
    return (Pomme) {
        .c = (Case) {
            .x = rand() % (nb_colonnes - 1),
            .y = rand() % (nb_lignes - 1)
        }
    };
}

int pomme_ajoute_pomme(ListePommes* pommes, Pomme p) {
    ListePommesEntry* entry = alloue_pomme(p);

    if (!entry)
        return 0;

    LIST_INSERT_HEAD(pommes, entry);

    return 1;
}

ListePommesEntry* alloue_pomme(Pomme p) {
    ListePommesEntry* apple = malloc(sizeof(ListePommesEntry));
    if (apple){
        apple->p = p;
        apple->next = NULL;
    }
    return apple;
}

int pomme_liste_supprime_pomme(ListePommes* pommes, Case c) {
    ListePommesEntry* entry;
    ListePommesEntry* prev = NULL;

    LIST_FOREACH(entry, pommes) {
        if (entry->p.c.x == c.x && entry->p.c.y == c.y) {
            if (prev)
                prev->next = entry->next;
            else // Le premier élement est celui recherché
                pommes->first = entry->next;

            free(entry);
            return 1;
        }

        prev = entry;
    }

    return 0;
}
