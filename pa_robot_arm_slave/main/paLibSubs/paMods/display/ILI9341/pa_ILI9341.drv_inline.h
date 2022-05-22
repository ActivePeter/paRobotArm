// #include "pa_ILI9341.drv_inline.inc.h"

inline void initGpio()
{
    _G_paGPIO.init(
        N_paGPIO::Mode_Output,
        Conf_ILI9341_CS);
    _G_paGPIO.init(
        N_paGPIO::Mode_Output,
        Conf_ILI9341_DC);
    _G_paGPIO.init(
        N_paGPIO::Mode_Output,
        Conf_ILI9341_RST);
}

inline void setCS(uint8_t state)
{
    _G_paGPIO.write(Conf_ILI9341_CS, state);
}
inline void setDC(uint8_t state)
{
    _G_paGPIO.write(Conf_ILI9341_DC, state);
}
inline void setRST(uint8_t state)
{
    _G_paGPIO.write(Conf_ILI9341_RST, state);
}
inline void delayMs(uint32_t ms)
{
    _G_paBase.delayMs(ms);
}
inline void transmit(char spiId, unsigned char *data, unsigned int len)
{
    _G_paSPI.transmit(spiId, data, len);
}