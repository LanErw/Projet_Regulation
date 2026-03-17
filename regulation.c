    #include <stdio.h>
	 #include <stdlib.h>
    #include "regulation.h"
	 
float regulationTest(int regul,float consigne,float* tabT, int nT){
	float cmd;
	for(int i=0; i<nT; i++){
		if (tabT[i] < consigne){
			cmd = regul;
		}
		else{
			cmd = 0;
		}
	}
	return cmd;
}

float regulation(int regul, float consigne, float tint, float* error_sum, float* prev_error, int first_iteration) {
	float commande = 0.0;
	float erreur = consigne - tint;
	
	if (regul == 1) {
		if (tint < consigne) {
			commande = 50.0;
		} else {
			commande = 0.0;
		}
	} 
	else if (regul == 2) {
		float kp = 1.1, ki = 0.2, kd = 0.15;

		if (first_iteration) {
			commande = kp * erreur;
			*error_sum = erreur;
		} else {
			*error_sum += erreur;
			float derivee = erreur - (*prev_error);
			
			commande = (kp * erreur) + (ki * (*error_sum)) + (kd * derivee);
		}
		
		*prev_error = erreur;

		if (commande > 100.0) commande = 100.0;
		if (commande < 0.0) commande = 0.0;
	}

	return commande;
}

