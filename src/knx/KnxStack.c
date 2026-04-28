#include "KnxStack.h"
#include "KnxTpUart.h"
#include "KnxAddressTable.h"
#include "KnxAssocTable.h"
#include "KnxComObject.h"
#include "KnxProgramming.h"
#include "CemiFrame.h"

void KNX_Stack_Init(void)
{
    KNX_TpUart_Init();
    KNX_AddressTable_Init();
    KNX_AssocTable_Init();
    KNX_ComObject_Init();
    KNX_Programming_Init();
}

void KNX_Stack_Process(void)
{
    KNX_TpUart_Process();
    KNX_Programming_Process();
}
