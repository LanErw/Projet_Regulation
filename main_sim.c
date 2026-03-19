#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "visualisationC.h"
#include "visualisationT.h"
#include "consigne.h"
#include "simulateur.h"
#include "regulation.h"

int main() {
    float consigne_f = 15.0f;
    temp_t myTemp = {10.0f, 5.0f};
    float puissance = 0.0f;
    float tabT[10000];
    int nT = 0;
    float preverror = 0.0f;
    my_pid_t *pid = malloc(sizeof(my_pid_t));
    pid->Kp = 1.1;
    pid->Ki = 0.2;
    pid->Kd = 0.15;
    pid->integral = 0.0;
    int first_iteration = 1;
    struct simParam_s *sim_param = simConstruct(myTemp);
    if (sim_param == NULL) {
        free(pid);
        return 1;
    }

    while (1) {
        consigne_f = consigne(consigne_f);
        puissance = regulation(1, consigne_f, myTemp.interieure, pid, preverror, first_iteration);
        visualisationC(puissance);
        myTemp = simCalc(puissance, sim_param);
        visualisationT(myTemp);
        tabT[nT] = myTemp.interieure;
        nT++;
        preverror = consigne_f - myTemp.interieure;
        if(first_iteration == 1){
            first_iteration = 0;
        }
        sleep(1);
    }

    simDestruct(sim_param);
    free(pid);
    return 0;
}