#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "visualisationC.h"



void visualisationC(float puissance_f) {
   char chauffage[10] = "false";
   float tinterieure = 0.0f;
   float texterieure = 0.0f;
   if(fopen(".verrouData","wx")==NULL){
      return;
   }
   FILE *fichier = fopen("data.txt", "r");
   if (fichier == NULL) {
      remove(".verrouData");
      return;
   }

   fscanf(fichier, "%s\n%f\n%f\n", chauffage, &tinterieure, &texterieure);

   fclose(fichier);

   fichier = fopen("data.txt", "w");
   if (fichier == NULL) {
      remove(".verrouData");
      return;
   }

   if (puissance_f > 0) {
      fprintf(fichier, "%s\n%.2f\n%.2f\n", "true", tinterieure, texterieure);
   } else {
      fprintf(fichier, "%s\n%.2f\n%.2f\n", "false", tinterieure, texterieure);
   }

   fclose(fichier);
   remove(".verrouData");
}