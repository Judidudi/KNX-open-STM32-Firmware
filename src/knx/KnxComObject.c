#include "KnxComObject.h"

static KNX_ComObject_WriteCallback s_callbacks[KNX_COM_OBJECT_MAX];

void KNX_ComObject_Init(void)
{
    for (uint8_t i = 0; i < KNX_COM_OBJECT_MAX; i++) {
        s_callbacks[i] = 0;
    }
}

void KNX_ComObject_RegisterWriteCallback(uint8_t coNum, KNX_ComObject_WriteCallback cb)
{
    if (coNum < KNX_COM_OBJECT_MAX) {
        s_callbacks[coNum] = cb;
    }
}

void KNX_ComObject_OnWrite(uint8_t coNum, const uint8_t *data, uint8_t len)
{
    if (coNum < KNX_COM_OBJECT_MAX && s_callbacks[coNum]) {
        s_callbacks[coNum](coNum, data, len);
    }
}
