#ifndef KNX_COM_OBJECT_H
#define KNX_COM_OBJECT_H

#include <stdint.h>

#define KNX_COM_OBJECT_MAX  16U

/* Flags: Communication / Read / Write / Transmit / Update  (KNX spec 03_03_07) */
#define KNX_CO_FLAG_C  (1U << 0)
#define KNX_CO_FLAG_R  (1U << 1)
#define KNX_CO_FLAG_W  (1U << 2)
#define KNX_CO_FLAG_T  (1U << 3)
#define KNX_CO_FLAG_U  (1U << 4)

typedef void (*KNX_ComObject_WriteCallback)(uint8_t coNum, const uint8_t *data, uint8_t len);

void KNX_ComObject_Init(void);
void KNX_ComObject_RegisterWriteCallback(uint8_t coNum, KNX_ComObject_WriteCallback cb);

/* Called by KnxStack when a GroupValueWrite arrives for coNum */
void KNX_ComObject_OnWrite(uint8_t coNum, const uint8_t *data, uint8_t len);

#endif /* KNX_COM_OBJECT_H */
