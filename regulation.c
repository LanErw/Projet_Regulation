    #include <stdio.h>
	 #include <stdlib.h>
    #include "regulation.h"
	 
float regulation(int regul, float consigne, float tint, float* error_sum, float* prev_error, int first_iteration) {
    float commande = 0.0;
    float erreur = consigne - tint;

    if (regul == 1) {
        // Tout ou Rien : 50% si tint < consigne, 0 sinon
        if (tint < consigne) {
            commande = 50.0;
        } else {
            commande = 0.0;
        }
    } 
    else if (regul == 2) {
        float kp = 1.1, ki = 0.2, kd = 0.15;

        if (first_iteration) {
            // Première itération : seulement le terme P
            commande = kp * erreur;
            *error_sum = erreur;
            *prev_error = erreur;
        } else {
            *error_sum += erreur;
            float derivee = erreur - (*prev_error);
            commande = (kp * erreur) + (ki * (*error_sum)) + (kd * derivee);
            *prev_error = erreur;
        }

        // Saturation linéaire entre 0 et 100
        if (commande > 100.0) commande = 100.0;
        if (commande < 0.0)   commande = 0.0;
    }

    return commande;
}

	float regulationTest(int regul, float csgn, float* tabT, int nT) {
    float cmd = 100.0;
    float error_sum = 0.0;
    float prev_error = 0.0;
    int first_iteration = 1;

    for (int i = 0; i < nT; i++) {
        cmd = regulation(regul, csgn, tabT[i], &error_sum, &prev_error, first_iteration);
        first_iteration = 0;
    }
    return cmd;
}
