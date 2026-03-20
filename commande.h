#ifndef COMMANDE_H
#define COMMANDE_H

#include <stdint.h>
#include "ftd2xx.h"

#ifdef __cplusplus
extern "C" {
#endif

FT_STATUS commande_send(FT_HANDLE handle, float puissance, DWORD *bytesWritten);

#ifdef __cplusplus
}
#endif

#endif /* COMMANDE_H */