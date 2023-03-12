#include "interface.h"
#include "list.h"
#include "types.h"
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
    interface_init_colors();
    interface_afficher_quadrillage(mon);

    return game_win;
}

void interface_init_colors() {
    start_color();

    init_pair(PAIR_SERPENT, COLOR_GREEN, COLOR_BLACK);
    init_pair(PAIR_POMME_NORMALE, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(PAIR_POMME_DOUBLE, COLOR_YELLOW, COLOR_BLACK);
    init_pair(PAIR_POMME_EMPOISONNE, COLOR_RED, COLOR_BLACK);
    init_pair(PAIR_BOX, COLOR_BLUE, COLOR_BLACK);
}

void interface_afficher_quadrillage(Monde mon) {
    wattron(game_win, COLOR_PAIR(PAIR_BOX) | A_BOLD);
    box(game_win, 0, 0);
    wattroff(game_win, COLOR_PAIR(PAIR_BOX) | A_BOLD);
}

void interface_afficher_pomme(Pomme pom) {

    int mode;

    switch (pom.type) {
    case POMME_DOUBLE:
        mode = PAIR_POMME_DOUBLE;
        break;
    case POMME_EMPOISOINNE:
        mode = PAIR_POMME_EMPOISONNE;
        break;
    default:
        mode = PAIR_POMME_NORMALE;
    }
    mvwaddch(game_win, pom.c.y + 1, pom.c.x + 1, 'o' | COLOR_PAIR(mode));
}

void interface_afficher_pommes(const ListePommes* pommes) {
    ListePommesEntry* cell;
    
    LIST_FOREACH(cell, pommes) {
        interface_afficher_pomme(cell->p);
    }
}

void interface_afficher_serpent(const Serpent* ser) {
    // On retient la dernière case supprimée afin de la remplacer
    // par un espace, pour éviter un clear de la fenêtre.
    static Case last_case = {-1, -1};
    ListeSerpentEntry* cell;

    if (last_case.x != -1 && last_case.y != -1)
        mvwaddch(game_win, last_case.y + 1, last_case.x + 1, ' ');

    last_case = LIST_FIRST(&ser->snake_cases)->c;

    LIST_FOREACH(cell, &ser->snake_cases) {
        int attrmode = cell == LIST_LAST(&ser->snake_cases) ? A_BOLD : A_NORMAL;
        mvwaddch(
            game_win,
            cell->c.y + 1, cell->c.x + 1,
            ACS_DIAMOND | COLOR_PAIR(PAIR_SERPENT) | attrmode);
    }
}

void interface_afficher_monde(Monde mon) {
    // wclear(game_win);
    interface_afficher_quadrillage(mon);
    interface_afficher_pommes(&mon.apples);
    interface_afficher_serpent(&mon.snake);

    if (mon.params.sound) beep();

    mvprintw(
        LINES - 1, COLS / 2 - sizeof(STR_SCORE) / 2,
        STR_SCORE, mon.score);

    wrefresh(game_win);
    wrefresh(stdscr);
}

Error interface_piloter(Monde *mon) {
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
        case 'q':
            return ERR_EXIT;
        default:
            break;
    }

    return ERR_NONE;
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
