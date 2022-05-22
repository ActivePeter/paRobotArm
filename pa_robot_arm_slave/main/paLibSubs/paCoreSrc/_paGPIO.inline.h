#include "_paGPIO.inline.inc.h"
/**
 * related article about gpio
 * https://blog.csdn.net/libin55/article/details/107091644/
 * s2 https://blog.csdn.net/zhong1213/article/details/117930199
 * check this article for detailed pin functions
*/
paErr init(N_paGPIO::Mode gpioMode, gpio_num_t pin);

inline void write(gpio_num_t pin, char status)
{
    gpio_set_level(pin, status);
}
inline char read(gpio_num_t pin)
{
    return gpio_get_level(pin);
}