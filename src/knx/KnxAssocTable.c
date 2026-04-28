#include "KnxAssocTable.h"

void KNX_AssocTable_Init(void)
{
}

uint8_t KNX_AssocTable_GetCount(void)
{
    volatile const uint8_t *p = (volatile const uint8_t *)KNX_ASSOC_TABLE_BASE;
    return (uint8_t)((p[0] << 8) | p[1]);
}

uint8_t KNX_AssocTable_FindCoNum(uint8_t gaIndex)
{
    uint8_t count = KNX_AssocTable_GetCount();
    volatile const uint8_t *p = (volatile const uint8_t *)(KNX_ASSOC_TABLE_BASE + 2U);
    for (uint8_t i = 0; i < count; i++) {
        if (p[i * 2U] == gaIndex) return p[i * 2U + 1U];
    }
    return 0xFFU;
}

uint8_t KNX_AssocTable_FindGaIndex(uint8_t coNum)
{
    uint8_t count = KNX_AssocTable_GetCount();
    volatile const uint8_t *p = (volatile const uint8_t *)(KNX_ASSOC_TABLE_BASE + 2U);
    for (uint8_t i = 0; i < count; i++) {
        if (p[i * 2U + 1U] == coNum) return p[i * 2U];
    }
    return 0U;
}
