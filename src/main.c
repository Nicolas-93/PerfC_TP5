#include "interface.h"
#include "serpent.h"
#include "monde.h"
#include <ncurses.h>
#include <locale.h>

#define SEC_TO_USEC(x) ((x) * 1e6)

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    initscr();

    Monde monde = monde_initialiser(20, 20, 5, 5);
    WINDOW* game_win = interface_initialiser(monde);
    
    interface_afficher_monde(monde);
    
    while (1) {
        monde_evoluer_serpent(&monde);
        interface_afficher_monde(monde);
        usleep(SEC_TO_USEC(0.25));
        interface_piloter(&monde);
    }
}
