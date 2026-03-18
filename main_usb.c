#include "ftd2xx.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    FT_HANDLE ftHandle; 
    FT_STATUS ftStatus; 

    ftStatus = FT_Open(0,&ftHandle); 
    if (ftStatus == FT_OK) { 
        printf("Hello world!\n");
    } 
    else { 
        // FT_Open failed 
    }
}