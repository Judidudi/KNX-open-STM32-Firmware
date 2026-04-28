#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <stdint.h>

/* manifest: memoryLayout.parameterBase  (default 0x4400) */
#define KNX_PARAM_BASE  0x4400U

/* Add parameter offsets here, synchronized with the device manifest:
   #define P_<NAME>_OFFSET  <n>U  // manifest: parameters[id=<id>].memoryOffset */

#define KNX_PARAM_READ_U8(addr) \
    (*((volatile const uint8_t *)(addr)))
#define KNX_PARAM_READ_U16(addr) \
    ((uint16_t)((KNX_PARAM_READ_U8(addr) << 8) | KNX_PARAM_READ_U8((addr) + 1U)))

#endif /* PARAMETERS_H */
