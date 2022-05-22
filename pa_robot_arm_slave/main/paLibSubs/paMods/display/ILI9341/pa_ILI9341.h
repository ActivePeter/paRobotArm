

#ifndef __ILI9341_H__
#define __ILI9341_H__
// #include "paBase/_ForMod.h"
// #include "pa_ILI9341.drv_inline.inc.h"
#include "paCoreInc/all"
#include "Conf_ILI9341.h"

class pa_ILI9341
{

private: //drv inline function
#include "pa_ILI9341.drv_inline.h"

public:
  enum Rotation
  {
    Rotation_VERTICAL_1 = 0,
    Rotation_HORIZONTAL_1,
    Rotation_VERTICAL_2,
    Rotation_HORIZONTAL_2
  };

  void init(char spiId, Rotation Rotation);
  void flush(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Colour);
  void burst(uint16_t Colour, uint32_t Size);
  void setAddress(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);
  inline void transmitBuf(unsigned char *data, unsigned int len)
  {
    setDC(1);
    setCS(0);
    _G_paSPI.transmit(spiId, data, len);
    setCS(1);
  }
  unsigned char pa_ILI9341_burst_buffer[500];

private:
  short LCD_WIDTH;
  short LCD_HEIGHT;
  char spiId;

  const short BURST_MAX_SIZE = 500;

  void reset();
  void enable();

  void writeCommand(uint8_t Command);
  void writeData(uint8_t Command);

  void setRotation(Rotation Rotation);
};

#endif // __ILI9341_H__
