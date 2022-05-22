#ifndef __PASPI_H__
#define __PASPI_H__
#include "../base/_all.h"

class paSPI
{
private:
    /* data */
public:
    // void write();
    paErr init(char spiId);
    paErr transmit(char spiId, unsigned char *data, unsigned int len);

    // void receive();
};

extern paSPI _G_paSPI;
#endif // __PASPI_H__