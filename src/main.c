#define _GNU_SOURCE

#include "interface.h"
#include "serpent.h"
#include "monde.h"
#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>
#include "temps.h"
#include "ini_parser.h"
#include "list.h"

#define SEC_TO_USEC(x) ((clock_t) ((x) * (clock_t) (1e6)))
#define MS_TO_SEC(x) ((double) (x) / (double) 1000)
#define SNAKE_SPEED

int main(int argc, char* argv[]) {

    int error = 0;
    int quit = false;

    Monde monde = parse_conf("serpent.ini");
    // Monde monde = monde_initialiser(15, 25, 5, 5, 50);

    setlocale(LC_ALL, "");
    initscr();

    interface_initialiser(monde);
    interface_afficher_monde(monde);

    PeriodicChrono move_timing = temps_initialiser_attente(MS_TO_SEC(monde.params.duree_tour));

    while (!quit) {

        quit = interface_piloter(&monde);

        if (!monde.pause) {
            if (temps_verifier_depasse(&move_timing)) {
                error = monde_evoluer_serpent(&monde);
                interface_afficher_monde(monde);
            }
        }

        if (error == SERPENT_MORT) {
            interface_afficher_message(STR_PERDU);
            break;
        } else if (error == ERR_ALLOC)
            break;
        
        // 60 fps - Empêche la latence pour les évènements clavier
        usleep(SEC_TO_USEC(0.016));
    }

    monde_libere(&monde);

    nodelay(stdscr, FALSE);
    getch();
    endwin();

    return EXIT_SUCCESS;
}
