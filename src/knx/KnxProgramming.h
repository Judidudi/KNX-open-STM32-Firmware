#ifndef KNX_PROGRAMMING_H
#define KNX_PROGRAMMING_H

#include <stdint.h>

void    KNX_Programming_Init(void);
void    KNX_Programming_Process(void);
void    KNX_Programming_ButtonFlag(void);  /* call from GPIO ISR */
uint8_t KNX_Programming_IsActive(void);

#endif /* KNX_PROGRAMMING_H */
