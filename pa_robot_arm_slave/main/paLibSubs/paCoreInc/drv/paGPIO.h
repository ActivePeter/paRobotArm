#ifndef __PAGPIO_H__
#define __PAGPIO_H__
#include "../base/_all.h"
//inline 函数所需头文件
#include "_paGPIO.types.h"
#include "paCoreSrc/_paGPIO.inline.inc.h"
class paGPIO
{
private:
    /* data */
public:
//具体inline函数实现
/**
 * functions as following need 2 be created in "paCoreSrc/_paGPIO.inline.h"
 * the detailed gpio type is from platform
 * 
 * paErr init(N_paGPIO::Mode gpioMode, gpio_type pin);
 *
 * inline void write(gpio_type pin, char status)
 * {
 *    gpio_set_level(pin, status);
 * }
 * inline char read(gpio_type pin)
 * {
 *     return gpio_get_level(pin);
 * }
*/
#include "paCoreSrc/_paGPIO.inline.h"
};
extern paGPIO _G_paGPIO;

#endif // __PAGPIO_H__