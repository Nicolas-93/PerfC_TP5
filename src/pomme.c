#include "pomme.h"
#include "case.h"
#include <stdlib.h>

Pomme pomme_aleatoire(int nb_lignes, int nb_colonnes) {
    return (Pomme) {
        .apple_case = (Case) {
            .x = rand() % (nb_colonnes - 1),
            .y = rand() % (nb_lignes - 1)
        }
    };
}

int pomme_ajoute_pomme(ListePommes* pommes, Pomme p) {
    ListePommesEntry* entry = alloue_pomme(p);

    if (!entry)
        return 0;

    entry->next = *pommes;
    *pommes = entry;

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
