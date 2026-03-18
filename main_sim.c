#include <stdio.h>
#include <stdlib.h>
#include "visualisationC.h"
#include "visualisationT.h"
#include "consigne.h"
#include "simulateur.h"
#include "regulation.h"

int main() {
    float consigne_f = 0.0f;
    temp_t myTemp = {0.0f, 0.0f};
    struct simParam_s* simConstruct(myTemp);
    float puissance = 0.0f;
    // float tabT[10] = {0.0f};
    // int nT = 10;
    // trace.txt : temps, puis, text, tint
    while (1) {
        consigne_f = consigne(consigne_f);
        myTemp = simCalc(consigne_f, simConstruct);
        visualisationC(consigne_f);
        visualisationT(myTemp);
        sleep(1);
    }

    return 0;
}