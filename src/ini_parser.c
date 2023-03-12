#define _GNU_SOURCE
#include "monde.h"
#include "ini_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Itère sur un fichier de configuration au format ini.
 * Alloue aux adresses opt_name et opt_val, la place nécessaire.
 * 
 * @param f 
 * @param opt_name 
 * @param opt_val 
 * @return Retourne EOF lorsque tous les paramètres ont
 * été lus. 1 en cas d'erreur de lecture
 */
int ini_getopt(FILE* f, char** opt_name, char** opt_val) {

    // La fonction scanf de GNU, supporte l'allocation dynamique
    // avec la spécificateur m.
    int n_read = fscanf(f, "%ms = %ms", opt_name, opt_val);

    if (n_read == EOF) {
        return EOF;
    }

    if (n_read < 2) {
        return -2;
    }

    return 0;
}

int boolean_string(char* str) {
    if (strcmp(str, "true") == 0)
        return true;

    else if (strcmp(str, "false") == 0)
        return false;

    return -1;
}

Monde parse_conf(char* filename) {
    Monde m = monde_config_par_defaut(32, 16, 5, 5, 50);
    FILE* f;

    if (!(f = fopen(filename, "r"))) {
        fprintf(stderr,
                "Veuillez situer le fichier de configuration "
                "'serpent.ini' dans le dossier de l'exécutable, "
                "et vous situer dans le dossier build\n");
        exit(EXIT_FAILURE);
    }

    char *name = NULL, *val = NULL;
    int err = 0;

    while ((err = ini_getopt(f, &name, &val)) != EOF) {
        
        if (err == -2) {
            fprintf(stderr, "Erreur dans le parsing des paramètres du fichier de configuration INI.\n");
            exit(EXIT_FAILURE);
        }

        if (IS_OPT(name, "largeur")) {
            if ((m.largeur = atoi(val)) < 5) {
                fprintf(stderr, "La largeur minimale est 5\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (IS_OPT(name, "hauteur")) {
            if ((m.hauteur = atoi(val)) < 5) {
                fprintf(stderr, "La hauteur minimale est 5\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (IS_OPT(name, "nombre_pommes")) {
            if ((m.nb_pommes = atoi(val)) < 1) {
                fprintf(stderr, "Un minimum d'une pomme est requis.\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (IS_OPT(name, "taille_serpent")) {
            if ((m.snake.len = atoi(val)) < 1) {
                fprintf(stderr, "La taille minimale du serpent est 1.\n");
                exit(EXIT_FAILURE);
            } 
        }
        else if (IS_OPT(name, "duree_tour")) {
            if ((m.params.duree_tour = atoi(val)) < 10) {
                fprintf(stderr, "La duree d'un tick doit être au minimum de 10ms.\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (IS_OPT(name, "pourcentage_pommes_empoisonnes")) {
            if ((m.params.pourcentage_empoisonnees = atoi(val)) < 0 || 
                m.params.pourcentage_empoisonnees > 100) {
                fprintf(stderr, "Veuillez paramétrer un pourcentage entre 0 et 100.\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (IS_OPT(name, "son")) {
            if ((m.params.sound = boolean_string(val)) == -1) {
                fprintf(stderr, "Booléeen invalide pour l'option %s\n", name);
                exit(EXIT_FAILURE);
            }
        }
        else {
            fprintf(stderr, "Paramètre inexistant : %s\n", name);
            exit(EXIT_FAILURE);
        }

        // Cette gestion des frees devrait être dans ini_getopt
        free(name);
        free(val);
    }

    fclose(f);

    monde_initialiser_aux(&m);
    return m;
}
