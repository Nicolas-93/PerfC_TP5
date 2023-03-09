#include "interface.h"
#include <ncurses.h>
#include <string.h>

WINDOW* game_win = NULL;

/**
 * @brief Initialise la sous-fenêtre ncurses du monde.
 * 
 * @param mon 
 */
WINDOW* interface_initialiser(Monde mon) {
    game_win = subwin(
        stdscr,
        mon.hauteur + 2, mon.largeur + 2,
        LINES / 2 - mon.hauteur / 2,
        COLS / 2 - mon.largeur / 2);
    
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    
    keypad(game_win, TRUE);
    nodelay(game_win, TRUE);
    
    noecho();
    curs_set(FALSE);
    
    interface_afficher_quadrillage(mon);

    return game_win;
}

void interface_afficher_quadrillage(Monde mon) {
    box(game_win, 0, 0);
    // wborder(
    //     game_win,
    //     ACS_VLINE, ACS_VLINE,
    //     115 | A_ALTCHARSET, 111 | A_ALTCHARSET,
    //     0, 0, 0, 0);
}

void interface_afficher_pomme(Pomme pom) {
    mvwaddch(game_win, pom.c.y + 1, pom.c.x + 1, 'o');
}

void interface_afficher_pommes(ListePommes pomme) {
    for (ListePommesEntry* cell = pomme;
         cell;
         cell = cell->next) {
        interface_afficher_pomme(cell->p);
    }
}

void interface_afficher_serpent(Serpent ser) {
    // On retient la dernière case supprimée afin de la remplacer
    // par un espace, pour éviter un clear de la fenêtre.
    static Case last_case = {-1, -1};

    if (last_case.x != -1 && last_case.y != -1)
        mvwaddch(game_win, last_case.y + 1, last_case.x + 1, ' ');

    for (ListeSerpentEntry* cell = ser.snake_cases;
         cell;
         cell = cell->next) {
        if (cell->next == NULL)
            last_case = cell->c;
        mvwaddch(game_win, cell->c.y + 1, cell->c.x + 1, ACS_DIAMOND);
    }
}

void interface_afficher_monde(Monde mon) {
    // wclear(game_win);
    interface_afficher_quadrillage(mon);
    interface_afficher_pommes(mon.apples);
    interface_afficher_serpent(mon.snake);

    mvprintw(
        LINES - 1, COLS / 2 - sizeof(STR_SCORE) / 2,
        STR_SCORE, mon.eaten_apples);

    wrefresh(game_win);
    wrefresh(stdscr);
}

int interface_piloter(Monde *mon) {
    int c = wgetch(game_win);
    switch (c) {
        case KEY_UP:
            mon->snake.dir = UP;
            break;
        case KEY_DOWN:
            mon->snake.dir = DOWN;
            break;
        case KEY_LEFT:
            mon->snake.dir = LEFT;
            break;
        case KEY_RIGHT:
            mon->snake.dir = RIGHT;
            break;
        case 'p':
            mon->pause ^= 1;
            break;
        default:
            break;
    }

    return c;
}

void interface_afficher_message(char* msg) {
    move(LINES - 2, 0);
    clrtoeol();
    mvprintw(LINES - 2, COLS / 2 - strlen(msg) / 2, msg);
    wrefresh(stdscr);
}


/**
 * @brief Dessine un rectangle de coordonnées (x1, y1) à (x2, y2)
 * avec mvhline et mvvline.
 * 
 * @param x1
 * @param y1 
 * @param x2 
 * @param y2 
 */
void interface_dessine_rectangle(int x1, int y1, int x2, int y2) {
    mvhline(y1, x1, 0, x2 - x1);
    mvhline(y2, x1, 0, x2 - x1);
    mvvline(y1, x1, 0, y2 - y1);
    mvvline(y1, x2, 0, y2 - y1);
}
