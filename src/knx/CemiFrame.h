#ifndef CEMI_FRAME_H
#define CEMI_FRAME_H

#include <stdint.h>

#define CEMI_MAX_DATA  14U

/* Message codes (KNX spec 03_06_03) */
#define CEMI_MC_L_DATA_REQ  0x11U
#define CEMI_MC_L_DATA_CON  0x2EU
#define CEMI_MC_L_DATA_IND  0x29U

typedef struct {
    uint16_t src;
    uint16_t dst;
    uint8_t  data[CEMI_MAX_DATA];
    uint8_t  dataLen;
    uint8_t  flags;
} CemiFrame_t;

/* Returns number of bytes written, or -1 on error */
int CEMI_Encode(const CemiFrame_t *f, uint8_t *buf, uint8_t bufLen);

/* Returns 0 on success, -1 on error */
int CEMI_Decode(const uint8_t *buf, uint8_t len, CemiFrame_t *out);

#endif /* CEMI_FRAME_H */
