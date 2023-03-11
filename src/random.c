#include "random.h"
#include <stdlib.h>

/**
 * @brief Renvoie un nombre aléatoire entre 0 et n.
 * 
 * @param n 
 * @return double 
 */
inline double rand_double(double n) {
    return (double)rand() / (double)(RAND_MAX / n);
}

/**
 * @brief Renvoie un nombre aléatoire entre a et b.
 * 
 * @param a 
 * @param b 
 * @return double 
 */
inline double uniform(double a, double b) {
    return a + (b - a) * rand_double(1);
}
/**
 * @brief Renvoie un booléen aléatoire.
 * 
 * @return int 
 */
inline int random_bool() {
    return rand() > (RAND_MAX / 2);
}

/**
 * @brief Renvoie aléatoirement un entier négatif
 * ou positif.
 * 
 * @return int 
 */
inline int random_direction() {
    return random_bool() == 0 ? -1 : 1;
}
