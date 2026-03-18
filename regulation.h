#include <stdio.h>
#include <stdlib.h>
#include "define.h" 

typedef struct {
    float Kp;
    float Ki;
    float Kd;
    float integral;
} my_pid_t;

float regulation(int regul, float consigne, float tint, my_pid_t *pid, float preverror, int first_iteration);
float regulationTest(int regul,float consigne,float* tabT, int nT);
