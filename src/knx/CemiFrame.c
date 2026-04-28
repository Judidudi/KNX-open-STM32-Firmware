#include "CemiFrame.h"

int CEMI_Encode(const CemiFrame_t *f, uint8_t *buf, uint8_t bufLen)
{
    if (!f || !buf || bufLen < (uint8_t)(11U + f->dataLen)) return -1;

    buf[0]  = CEMI_MC_L_DATA_REQ;
    buf[1]  = 0x00U;                /* add-info length */
    buf[2]  = 0xBCU;               /* ctrl1: standard frame, no repeat, broadcast, prio normal */
    buf[3]  = 0xE0U;               /* ctrl2: group addr, hop count 6 */
    buf[4]  = (uint8_t)(f->src >> 8);
    buf[5]  = (uint8_t)(f->src);
    buf[6]  = (uint8_t)(f->dst >> 8);
    buf[7]  = (uint8_t)(f->dst);
    buf[8]  = f->dataLen;
    buf[9]  = 0x00U;               /* TPCI */
    buf[10] = 0x80U;               /* APCI GroupValueWrite */

    for (uint8_t i = 0; i < f->dataLen; i++) {
        buf[11U + i] = f->data[i];
    }
    return (int)(11U + f->dataLen);
}

int CEMI_Decode(const uint8_t *buf, uint8_t len, CemiFrame_t *out)
{
    if (!buf || !out || len < 11U) return -1;

    out->src     = (uint16_t)((buf[4] << 8) | buf[5]);
    out->dst     = (uint16_t)((buf[6] << 8) | buf[7]);
    out->dataLen = buf[8];
    out->flags   = buf[2];

    if (out->dataLen > CEMI_MAX_DATA || len < (uint8_t)(11U + out->dataLen)) return -1;

    for (uint8_t i = 0; i < out->dataLen; i++) {
        out->data[i] = buf[11U + i];
    }
    return 0;
}
