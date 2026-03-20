#include "commande.h"

FT_STATUS commande_send(FT_HANDLE handle, float puissance, DWORD *bytesWritten) {
    // Convert the float to a byte array
    int puissance_f = (int)(puissance/100*127); // Ensure the float is in the correct format
    uint8_t buffer[1];
    memcpy(buffer, &puissance_f, sizeof(puissance_f)); // Copy the float into the byte array

    // Send the byte array over the FTDI interface
    return FT_Write(handle, buffer, 1, bytesWritten);
}