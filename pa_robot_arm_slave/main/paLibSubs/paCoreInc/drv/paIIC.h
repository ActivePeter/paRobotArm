class paIIC;
struct ByteArr;

#ifndef __PAIIC_H__
#define __PAIIC_H__

#include "../base/_all.h"

class paIIC
{
private:
    /* data */
public:
    /**
     * @brief 初始化对应id的iic 
    */
    uint8_t init(unsigned char iicId);

    /** 
     * @brief 写iic
     * @param addr   器件地址
     * @param length   数据体长度，可以为0
     * @param data_t   数据体指针
     */
    uint8_t writeLen(unsigned char iicId, unsigned char addr, unsigned char length, ByteArr data_wr[]);
};
extern paIIC _G_paIIC;

#endif // __PAIIC_H__