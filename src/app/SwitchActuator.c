#include "SwitchActuator.h"
#include "../knx/KnxComObject.h"

/* manifest: comObjects[id=co_switch_ch1].number */
#define CO_SWITCH_CH1  0U

static volatile uint8_t s_pendingValue = 0;
static volatile uint8_t s_hasPending   = 0;

static void OnSwitch(uint8_t coNum, const uint8_t *data, uint8_t len)
{
    (void)coNum;
    if (len < 1U) return;
    s_pendingValue = data[0] & 0x01U;
    s_hasPending   = 1U;
}

void APP_SwitchActuator_Init(void)
{
    KNX_ComObject_RegisterWriteCallback(CO_SWITCH_CH1, OnSwitch);
    /* TODO: configure relay GPIO output */
}

void APP_SwitchActuator_Process(void)
{
    if (!s_hasPending) return;
    s_hasPending = 0;
    /* TODO: set relay GPIO to s_pendingValue */
}
