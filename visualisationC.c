#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "visualisationC.h"


void visualisationC(float puissance_f){
   const char *data = "data.txt";
   char ligne[100];
   char chauffage[10] = "false";
   float tinterieure = 0.0f;
   float texterieure = 0.0f;

   FILE *fichier = fopen(data, "r");
   if(fichier == NULL){
      return;
   }
   
   if(fgets(ligne, sizeof(ligne), fichier)){
      size_t len = strlen(ligne);
      if(strcmp(ligne, "true") == 0){
         strcpy(chauffage, "true");
      } else {
         strcpy(chauffage, "false");
      }
   }

   if(fgets(ligne, sizeof(ligne), fichier)){
      tinterieure = strtof(ligne, NULL);
   }

   if(fgets(ligne, sizeof(ligne), fichier)){
      texterieure = strtof(ligne, NULL);
   }

   fclose(fichier);

   fichier = fopen(data, "w");
   if(fichier == NULL){
      return;
   }
   fprintf(fichier, "%s\n%.2f\n%.2f\n", chauffage, tinterieure, texterieure);
   fclose(fichier);
}

