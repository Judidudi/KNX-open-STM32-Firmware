#include "KnxProgramming.h"

static uint8_t          s_progActive = 0;
static volatile uint8_t s_btnFlag    = 0;

void KNX_Programming_Init(void)
{
    s_progActive = 0;
    s_btnFlag    = 0;
    /* TODO: configure prog-button GPIO input + EXTI interrupt */
    /* TODO: configure prog-LED GPIO output, drive LOW */
}

void KNX_Programming_Process(void)
{
    if (!s_btnFlag) return;
    s_btnFlag    = 0;
    s_progActive ^= 1U;
    /* TODO: set prog-LED GPIO to s_progActive */
}

void KNX_Programming_ButtonFlag(void)
{
    s_btnFlag = 1;
}

uint8_t KNX_Programming_IsActive(void)
{
    return s_progActive;
}
