#include "KnxTpUart.h"

static volatile uint8_t s_rxFlag = 0;

void KNX_TpUart_Init(void)
{
    /* TODO: configure UART peripheral for NCN5120 (19200 8E1) */
}

void KNX_TpUart_Process(void)
{
    if (!s_rxFlag) return;
    s_rxFlag = 0;
    /* TODO: read bytes from ring-buffer, assemble CEMI frame, dispatch */
}

int KNX_TpUart_Send(const uint8_t *buf, uint8_t len)
{
    /* TODO: write to UART TX via HAL_UART_Transmit */
    (void)buf; (void)len;
    return 0;
}

void KNX_TpUart_RxIrqHandler(void)
{
    s_rxFlag = 1;
}
