
#ifndef __pa_Xpt2046_H__
#define __pa_Xpt2046_H__

#include "paLibSubs/paCoreInc/all"
// #include "Arduino.h"
class pa_Xpt2046
{

public:
  pa_Xpt2046();
  void init(
      int screenW,
      int screenH,
      int xBeginRaw,
      int xEndRaw,
      int yBeginRaw,
      int yEndRaw,
      int sampleTime);

  //输入2个数
  uint8_t readRaw(uint16_t Coordinates[2]);
  void turnRawToScreen(uint16_t Coordinates[2]);
  uint8_t isPressed();

  void Hardware_SetCS(uint8_t state);

private:
  struct ConfigModel
  {
    int screenW;
    int screenH;
    int SampleCount;
    int xBeginRaw;
    int xEndRaw;
    int yBeginRaw;
    int yEndRaw;
  };
  //不要修改此处的数据。因为只是个默认值
  ConfigModel config = {
      0,
      0,
      2, // SampleCount,
      0,
      0,
      0,
      0};
  enum CMDs
  {
    CMD_RDY = 0X90,
    CMD_RDX = 0XD0
  };

  void Hardware_Init();
  uint8_t Hardware_ReadIRQ();
  void Hardware_setMOSI(uint8_t state);
  uint8_t Hardware_ReadMISO();
  void Hardware_setCLK(uint8_t state);

  uint16_t spiRead();
  void spiWrite(uint8_t value);
};

#endif