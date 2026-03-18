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
    float puissance = 0.0f;
    float tabT[10];
    int nT = 0;
    // trace.txt : temps, puis, text, tint

    while (1) {
        consigne_f = consigne(consigne_f);
        FILE* trace_pf = fopen("trace.txt", "r");
        if (trace_pf == NULL){
            printf("Erreur d'ouverture du fichier trace.txt\n");
            return;
        }
        for (int i = 0; i < nT; i++) {
            tabT[i] = tabT[i+1];
        }
        tabT[nT] = myTemp.interieure;
        puissance = regulationTest(2, consigne_f, tabT, nT);
        myTemp = simCalc(consigne_f, simConstruct(myTemp));
        visualisationC(puissance);
        visualisationT(myTemp);
        if(nT<9){
            nT++;
        }
        sleep(1);
    }

    return 0;
}