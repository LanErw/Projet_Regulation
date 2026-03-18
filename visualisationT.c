#include "visualisationT.h"

void visualisationT(temp_t myTemp){
    char chauffage[10] = "";
    if(fopen(".verrouData","wx")==NULL){
        return;
    }
    
    FILE *fichier = fopen("data.txt", "r");
    if(fichier == NULL){
        remove(".verrouData");
        return;
    }

    fscanf(fichier, "%s\n", chauffage);
    fclose(fichier);

    fichier = fopen("data.txt", "w");
    fprintf(fichier, "%s\n%0.2f\n%0.2f\n",chauffage,myTemp.interieure,myTemp.exterieure);
    fclose(fichier);
    remove(".verrouData");
}
