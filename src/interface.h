#ifndef UI_INCLUDED
#define UI_INCLUDED

#include <ncurses.h>
#include <unistd.h>
#include "pomme.h"
#include "serpent.h"
#include "monde.h"


void interface_afficher_quadrillage(Monde mon);
void interface_afficher_pomme(Pomme pom);
void interface_afficher_serpent(Serpent ser);
void interface_afficher_monde(Monde mon);
void interface_piloter(Monde *mon);

#endif
