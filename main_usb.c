#include "ftd2xx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "visualisationC.h"
#include "visualisationT.h"
#include "consigne.h"
#include "regulation.h"
#include "commande.h"
#include "releve.h"

int main(){
    FT_HANDLE ftHandle; 
    FT_STATUS ftStatus;
    ftStatus = FT_Open(0,&ftHandle);
    if(ftStatus == FT_OK) {
        float consigne_f = 15.0f;
        temp_t myTemp = {10.0f, 5.0f};
        float puissance = 0.0f;
        float preverror = 0.0f;
        my_pid_t *pid = malloc(sizeof(my_pid_t));
        pid->Kp = 1.1;
        pid->Ki = 0.2;
        pid->Kd = 0.15;
        pid->integral = 0.0;
        int first_iteration = 1;
        while (1) {
            consigne_f = consigne(consigne_f);
            puissance = regulation(2, consigne_f, myTemp.interieure, pid, preverror, first_iteration);
            FT_STATUS cmdStatus = commande_send(ftHandle, puissance, NULL);
            if (cmdStatus != FT_OK) {
                free(pid);
                printf("Erreur d'écriture sur la carte\n");
                return 1;
            }
            FT_STATUS rlvStatus = releve(ftHandle, &myTemp);
            if (rlvStatus != FT_OK) {
                free(pid);
                printf("Erreur de lecture sur la carte\n");
                return 1;
            }
            visualisationC(puissance);
            visualisationT(myTemp);
            preverror = consigne_f - myTemp.interieure;
            if(first_iteration == 1){
                first_iteration = 0;
            }
            sleep(1);
        }
        free(pid);
        FT_Close(ftHandle);
    }
    else {
        printf("Erreur d'ouverture de la carte\n");
        return 1;
    }
    return 0;
}