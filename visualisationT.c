#include "visualisationT.h"

void visualisationT(temp_t myTemp){
    char *data = "data.txt";
    char ligne[100];
    char chauffage[10] = "false";

    FILE *fichier = fopen(data, "r");
    if(fichier == NULL){
        return;
    }
    if(fopen(".verrouConsigne","x")==NULL || fopen(".verrouData","x")==NULL){
        fclose(fichier);
        return;
    }
    if(fgets(ligne, sizeof(ligne), fichier)) {
        strcpy(chauffage, ligne);
    }
    fclose(fichier);

    fichier = fopen(data, "w");
    fprintf(fichier, "%s\n%.2f\n%.2f\n",chauffage,myTemp.interieure,myTemp.exterieure);
    fclose(fichier);
    remove(".verrouConsigne");
    remove(".verrouData");
}
