#ifndef KNX_ASSOC_TABLE_H
#define KNX_ASSOC_TABLE_H

#include <stdint.h>

/* manifest: memoryLayout.associationTable  default 0x4100 */
#define KNX_ASSOC_TABLE_BASE  0x4100U

void    KNX_AssocTable_Init(void);
uint8_t KNX_AssocTable_GetCount(void);

/* Returns ComObject number for given 1-based GA index, or 0xFF if not found */
uint8_t KNX_AssocTable_FindCoNum(uint8_t gaIndex);

/* Returns 1-based GA index for given ComObject number, or 0 if not found */
uint8_t KNX_AssocTable_FindGaIndex(uint8_t coNum);

#endif /* KNX_ASSOC_TABLE_H */
