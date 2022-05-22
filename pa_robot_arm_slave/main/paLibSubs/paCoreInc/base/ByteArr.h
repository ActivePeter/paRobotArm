#ifndef __BYTEARR_H__
#define __BYTEARR_H__
#include "native.h"

struct ByteArr
{
    uint16_t len;
    uint8_t *arrPtr;
    ByteArr(uint16_t len, uint8_t *ptr) : len(len), arrPtr(ptr) {}
    ByteArr() {}
};
#endif // __BYTEARR_H__