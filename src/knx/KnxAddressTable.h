#ifndef KNX_ADDRESS_TABLE_H
#define KNX_ADDRESS_TABLE_H

#include <stdint.h>

/* manifest: memoryLayout.addressTable  default 0x4000 */
#define KNX_ADDR_TABLE_BASE  0x4000U

void     KNX_AddressTable_Init(void);
uint16_t KNX_AddressTable_GetPhysicalAddress(void);
uint16_t KNX_AddressTable_GetGroupAddress(uint8_t index);
uint8_t  KNX_AddressTable_GetCount(void);

#endif /* KNX_ADDRESS_TABLE_H */
