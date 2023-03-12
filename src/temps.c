#define _GNU_SOURCE

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "temps.h"


PeriodicChrono temps_initialiser_attente(double n) {
    // initialiser le temps d'attente à n secondes dans le futur
    PeriodicChrono chrono = {.sec_to_wait = n} ;

    clock_gettime(CLOCK_REALTIME, &chrono.temps_actuel);
    
    chrono.temps_futur.tv_sec = chrono.temps_actuel.tv_sec;
    chrono.temps_futur.tv_nsec = chrono.temps_actuel.tv_nsec + (time_t)(n * 1e9);

    chrono.temps_futur.tv_sec += chrono.temps_futur.tv_nsec / (time_t)(1e9);
    chrono.temps_futur.tv_nsec %= (time_t)(1e9);

    return chrono;
}

bool temps_verifier_depasse(PeriodicChrono* chrono) {
    // obtenir le temps actuel
    clock_gettime(CLOCK_REALTIME, &chrono->temps_actuel);

    // Si le temps actuel dépasse le temps futur
    if (chrono->temps_actuel.tv_sec > chrono->temps_futur.tv_sec ||
        (chrono->temps_actuel.tv_sec == chrono->temps_futur.tv_sec &&
         chrono->temps_actuel.tv_nsec >= chrono->temps_futur.tv_nsec)) {
        
        // mettre à jour le temps d'attente à n secondes dans le futur
        *chrono = temps_initialiser_attente(chrono->sec_to_wait);
        
        return true;
    }
    return false;
}

void temps_reinitialise_chrono(PeriodicChrono* chrono, double n) {
    // Le but c'est de réinitialiser un chrono avec une nouvelle quantité de temps.
    chrono->sec_to_wait = n;

    chrono->temps_futur.tv_sec = chrono->temps_actuel.tv_sec;
    chrono->temps_futur.tv_nsec = chrono->temps_actuel.tv_nsec + (time_t)(n * 1e9);

    chrono->temps_futur.tv_sec += chrono->temps_futur.tv_nsec / (time_t)(1e9);
    chrono->temps_futur.tv_nsec %= (time_t)(1e9);

}


