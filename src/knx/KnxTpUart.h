#ifndef KNX_TPUART_H
#define KNX_TPUART_H

#include <stdint.h>

void KNX_TpUart_Init(void);
void KNX_TpUart_Process(void);
int  KNX_TpUart_Send(const uint8_t *buf, uint8_t len);

/* Called from UART ISR – sets internal flag only, no processing here */
void KNX_TpUart_RxIrqHandler(void);

#endif /* KNX_TPUART_H */
