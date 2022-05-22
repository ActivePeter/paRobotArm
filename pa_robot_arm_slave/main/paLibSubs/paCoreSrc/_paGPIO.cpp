#include "paCoreInc/drv/paGPIO.h"
using namespace N_paGPIO;
/**
 * related article about gpio
 * https://blog.csdn.net/libin55/article/details/107091644/
 * s2 https://blog.csdn.net/zhong1213/article/details/117930199
 * check this article for detailed pin functions
*/
paErr paGPIO::init(Mode gpioMode, gpio_num_t pin)
{

    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;

    if (gpioMode == Mode_Output)
    {
        io_conf.mode = GPIO_MODE_OUTPUT;
    }
    else
    {
        io_conf.mode = GPIO_MODE_INPUT;
        switch (gpioMode)
        {
        case Mode_InputPullDown:
            io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
            break;
        case Mode_InputPullUp:
            io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
            break;
        default:
            break;
        }
    }
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = (1ULL << pin);
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    return E_Succ;
}
