#include "KnxAddressTable.h"

void KNX_AddressTable_Init(void)
{
}

uint16_t KNX_AddressTable_GetPhysicalAddress(void)
{
    /* Bytes [2..3] at base: PA_hi | PA_lo */
    volatile const uint8_t *p = (volatile const uint8_t *)KNX_ADDR_TABLE_BASE;
    return (uint16_t)((p[2] << 8) | p[3]);
}

uint16_t KNX_AddressTable_GetGroupAddress(uint8_t index)
{
    /* Entries start at byte 4, 2 bytes each; index is 0-based */
    volatile const uint8_t *p =
        (volatile const uint8_t *)(KNX_ADDR_TABLE_BASE + 4U + (uint16_t)index * 2U);
    return (uint16_t)((p[0] << 8) | p[1]);
}

uint8_t KNX_AddressTable_GetCount(void)
{
    volatile const uint8_t *p = (volatile const uint8_t *)KNX_ADDR_TABLE_BASE;
    /* count_hi/count_lo encodes (1 + number-of-GAs) */
    uint16_t raw = (uint16_t)((p[0] << 8) | p[1]);
    return (uint8_t)(raw > 0U ? raw - 1U : 0U);
}
