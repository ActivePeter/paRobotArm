#include "pa_xpt2046.h"
#include "Conf_pa_xpt2046.h"

void pa_Xpt2046::Hardware_Init()
{
    _G_paGPIO.init(N_paGPIO::Mode_InputNoPull, pa_Xpt2046_IRQ);
    _G_paGPIO.init(N_paGPIO::Mode_InputNoPull, pa_Xpt2046_MISO);

    _G_paGPIO.init(N_paGPIO::Mode_Output,      pa_Xpt2046_CS);
    _G_paGPIO.init(N_paGPIO::Mode_Output,      pa_Xpt2046_MOSI);
    _G_paGPIO.init(N_paGPIO::Mode_Output,      pa_Xpt2046_CLK);
    // pinMode(pa_Xpt2046_IRQ, INPUT);
    // pinMode(pa_Xpt2046_CS, OUTPUT);
    // pinMode(pa_Xpt2046_MOSI, OUTPUT);
    // pinMode(pa_Xpt2046_MISO, INPUT);
    // pinMode(pa_Xpt2046_CLK, OUTPUT);
}

uint8_t pa_Xpt2046::Hardware_ReadIRQ()
{
    return _G_paGPIO.read(pa_Xpt2046_IRQ);
}

void pa_Xpt2046::Hardware_SetCS(uint8_t state)
{
    _G_paGPIO.write(pa_Xpt2046_CS, state);
}

void pa_Xpt2046::Hardware_setMOSI(uint8_t state)
{
    _G_paGPIO.write(pa_Xpt2046_MOSI, state);
}

uint8_t pa_Xpt2046::Hardware_ReadMISO()
{
    return _G_paGPIO.read(pa_Xpt2046_MISO);
}

void pa_Xpt2046::Hardware_setCLK(uint8_t state)
{
    _G_paGPIO.write(pa_Xpt2046_CLK, state);
}