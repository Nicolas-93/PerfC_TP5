#define _GNU_SOURCE

#include "interface.h"
#include "serpent.h"
#include "monde.h"
#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include "temps.h"

#define SEC_TO_USEC(x) ((clock_t) ((x) * (clock_t) (1e6)))
#define SNAKE_SPEED

int main(int argc, char* argv[]) {
    int touche;
    int error = 0;
    int quit = false;
    int secondes_ecoulees;

    struct timeval debut, fin;
    gettimeofday(&debut, NULL);

    setlocale(LC_ALL, "");
    initscr();

    Monde monde = monde_initialiser(15, 25, 5, 5, 50);
    WINDOW* game_win = interface_initialiser(monde);

    interface_afficher_monde(monde);

    PeriodicChrono move_timing = temps_initialiser_attente(0.25);
    PeriodicChrono fin_jeu = temps_initialiser_attente(1000);

    while (!quit) {

        touche = interface_piloter(&monde);

        if (!monde.pause) {
            if (temps_verifier_depasse(&move_timing)) {
                error = monde_evoluer_serpent(&monde);
                interface_afficher_monde(monde);
            }

            double nv_tps = (double) (1000 - secondes_ecoulees);
            temps_reinitialise_chrono(&fin_jeu, nv_tps);


        } else {
            gettimeofday(&fin, NULL);
            secondes_ecoulees = fin.tv_sec - debut.tv_sec;
        }


        if (error == SERPENT_MORT) {
            interface_afficher_message(STR_PERDU);
            break;
        } else if (error == ERR_ALLOC)
            break;

        if (temps_verifier_depasse(&fin_jeu))
            break;    
        
        usleep(SEC_TO_USEC(0.016));
    }

    nodelay(stdscr, FALSE);
    getch();
    endwin();

    return EXIT_SUCCESS;
}
