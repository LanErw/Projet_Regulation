#include <stdio.h>
#include "ftd2xx.h"
#include "releve.h"

temp_t releve(FT_HANDLE handle) {
    temp_t temperature;
    temperature.interieure = 0.0f;
    temperature.exterieure = 0.0f;

    DWORD bytesRead;
    unsigned char octet;
    unsigned int SOT_ext = 0;
    unsigned int SOT_int = 0;

    // Synchronisation sur le 1er octet extérieur : 0000xxxx
    do {
        FT_Read(handle, &octet, 1, &bytesRead);
        if (bytesRead != 1) return temperature;
    } while ((octet & 0xF0) != 0x00);
    SOT_ext = (octet & 0x0F) << 8;

    // 2ème octet extérieur : 0001xxxx
    FT_Read(handle, &octet, 1, &bytesRead);
    if (bytesRead != 1 || (octet & 0xF0) != 0x10) return temperature;
    SOT_ext |= (octet & 0x0F) << 4;

    // 3ème octet extérieur : 0010xxxx
    FT_Read(handle, &octet, 1, &bytesRead);
    if (bytesRead != 1 || (octet & 0xF0) != 0x20) return temperature;
    SOT_ext |= (octet & 0x0F);

    temperature.exterieure = -39.64f + 0.04f * SOT_ext;

    // 1er octet intérieur : 1000xxxx
    FT_Read(handle, &octet, 1, &bytesRead);
    if (bytesRead != 1 || (octet & 0xF0) != 0x80) return temperature;
    SOT_int = (octet & 0x0F) << 8;

    // 2ème octet intérieur : 1001xxxx
    FT_Read(handle, &octet, 1, &bytesRead);
    if (bytesRead != 1 || (octet & 0xF0) != 0x90) return temperature;
    SOT_int |= (octet & 0x0F) << 4;

    // 3ème octet intérieur : 1010xxxx
    FT_Read(handle, &octet, 1, &bytesRead);
    if (bytesRead != 1 || (octet & 0xF0) != 0xA0) return temperature;
    SOT_int |= (octet & 0x0F);

    temperature.interieure = -39.64f + 0.04f * SOT_int;

    return temperature;
}