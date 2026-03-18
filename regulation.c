#include <stdio.h>
#include <stdlib.h>
#include "regulation.h"

#define TIME_STEP 10
float regulation(int regul, float consigne, float tint, my_pid_t *pid, float preverror, int first_iteration) {
    float commande = 0.0;
    if (regul == 1) {
        if (tint < consigne) {
            return 50.0;
        } else {
            return 0.0;
        }
    }
    float error = consigne - tint;
    commande = (pid->Kp) * error;
    if (first_iteration) {
        return commande;
    }
    commande += (pid->Ki)*((preverror + error) * TIME_STEP/2) + (pid->integral);
    pid->integral += (pid->Ki)*((preverror + error) * TIME_STEP/2);
    commande += (pid->Kd)*((error - preverror) / TIME_STEP);    
    if (commande > 100.0){
        commande = 100.0;
        //pid->integral -= (pid->Ki)*((preverror + error) * TIME_STEP/2);
    } 
    if (commande < 0.0){
        commande = 0.0;
        //pid->integral -= (pid->Ki)*((preverror + error) * TIME_STEP/2);
    }
    return commande;
}

float regulationTest(int regul, float csgn, float* tabT, int nT) {
    float cmd = 100.0;
    float preveror = 0;
    int first_iteration = 1;
    my_pid_t *pid = malloc(sizeof(my_pid_t));
    pid->Kp = 1.1;
    pid->Ki = 0.2;
    pid->Kd = 0.15;
    pid->integral = 0.0;
    for (int i = 0; i < nT; i++) {
        cmd = regulation(regul, csgn, tabT[i], pid, preveror, first_iteration);
        preveror = csgn - tabT[i];
        first_iteration = 0;
    }
    return cmd;
}