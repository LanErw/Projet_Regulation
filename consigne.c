#include "consigne.h"
#include <stdio.h>

float consigne(float thermostatPrec_f) {
    float thermostat_f = thermostatPrec_f;

    // Si le verrou EST présent, on retourne la consigne précédente sans toucher au fichier
    FILE *verrou = fopen(".verrouConsigne", "wx");
    if (verrou != NULL) {
        fclose(verrou);
        return thermostatPrec_f;
    }

    // Pas de verrou : on peut lire
    FILE *fichier = fopen("consigne.txt", "r");
    if (fichier != NULL) {
        float nouvelleConsigne_f;
        if (fscanf(fichier, "%f", &nouvelleConsigne_f) == 1) {
            thermostat_f = nouvelleConsigne_f;
        }
        fclose(fichier);
    }

    return thermostat_f;
    remove(".verrouConsigne");
}