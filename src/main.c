#include "knx/KnxStack.h"
#include "app/Application.h"

/* Declared in CubeIDE-generated Core/Src/main.c; resolved by linker. */
extern void SystemClock_Config(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    KNX_Stack_Init();
    APP_Init();

    while (1) {
        KNX_Stack_Process();
        APP_Process();
    }
}
