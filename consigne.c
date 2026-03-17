#include "consigne.h"

   float consigne(float thermostatPrec_f)
   {
      float thermostat_f = thermostatPrec_f;
      if (fopen(".verrouConsigne", "r") == NULL) {
         return thermostat_f;
      }
      
      FILE *fichier = fopen("consigne.txt", "r");
      if (fichier != NULL) {
         float nouvelleConsigne_f;
         if (fgets(fichier, "%f", &nouvelleConsigne_f) == 1) {
            thermostat_f = nouvelleConsigne_f;
         }
         fclose(fichier);
      }
      return thermostat_f;
   
   }
