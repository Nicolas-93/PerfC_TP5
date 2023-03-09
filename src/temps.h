#define _GNU_SOURCE

#include <sys/time.h>
#include <stdbool.h>

typedef struct PeriodicChrono {
    struct timespec temps_actuel;
    struct timespec temps_futur;
    double sec_to_wait;
} PeriodicChrono;

/**
 * @brief Initialise un point dans le futur à attendre
 * 
 * @param n Nombre de secondes à attendre
 * @return PeriodicChrono 
 */
PeriodicChrono temps_initialiser_attente(double n);

/**
 * @brief Détermine si on a atteint le point programmé
 * dans le futur.
 * 
 * @param chrono 
 * @return true 
 * @return false 
 */
bool temps_verifier_depasse(PeriodicChrono* chrono);
