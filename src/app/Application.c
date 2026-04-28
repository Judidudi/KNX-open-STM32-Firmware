#include "Application.h"
#include "SwitchActuator.h"

void APP_Init(void)
{
    APP_SwitchActuator_Init();
}

void APP_Process(void)
{
    APP_SwitchActuator_Process();
}
