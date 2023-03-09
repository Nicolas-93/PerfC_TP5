#ifndef UI_INCLUDED
#define UI_INCLUDED

#include <ncurses.h>
#include <unistd.h>
#include "pomme.h"
#include "serpent.h"
#include "monde.h"

#define STR_SCORE "Score: %3d"
#define STR_PERDU "Perdu !"

WINDOW* interface_initialiser(Monde mon);

/**
 * @brief Affiche le quadrillage du monde, à l'aide de box
 * ncurses.
 * 
 */
void interface_afficher_quadrillage(Monde mon);

/**
 * @brief Affiche la pomme pom selon sa position.
 * Cette fonction est vouée à dessiner la pomme
 * dans le quadrillage créé par interface_afficher_quadrillage.
 * 
 * @param pom 
 */
void interface_afficher_pomme(Pomme pom);

/**
 * @brief Affiche les pommes de la liste pomme.
 * 
 * @param pomme 
 */
void interface_afficher_pommes(ListePommes pomme);

/**
 * @brief Affiche le serpent ser selon sa position.
 * Cette fonction est vouée à dessiner le serpent dans le
 * quadrillage créé par la fonction interface_afficher_quadrillage. 
 * 
 * @param ser 
 */
void interface_afficher_serpent(Serpent ser);

/**
 * @brief Affiche le monde mon.
 * Ceci dessine la situation de jeu au complet : le quadrillage, les
 * pommes, le serpent et le nombre de pommes mangées.
 * 
 * @param mon 
 */
void interface_afficher_monde(Monde mon);

/**
 * @brief Détecte la pression sur une touche commandant
 * la direction du serpent du monde pointé par mon et qui la met à jour.
 * 
 * @param mon 
 */
int interface_piloter(Monde *mon);

/**
 * @brief Affiche le message msg à la dernière ligne
 * de la fenêtre principale, en effaçant son contenu
 * 
 * @param msg 
 */
void interface_afficher_message(char* msg);

#endif
