#include "pa_ILI9341.h"
/**
 * too long, so use single file
*/
void pa_ILI9341::init(char spiId1, Rotation Rotation)
{
    initGpio();
    spiId = spiId1;
    enable();
    reset();

    //SOFTWARE RESET
    this->writeCommand(0x01);
    this->delayMs(1000);

    writeCommand(0xEF);
    writeData(0x03);
    writeData(0x80);
    writeData(0x02);

    //POWER CONTROL A
    this->writeCommand(0xCB);
    this->writeData(0x39);
    this->writeData(0x2C);
    this->writeData(0x00);
    this->writeData(0x34);
    this->writeData(0x02);

    //POWER CONTROL B
    this->writeCommand(0xCF);
    this->writeData(0x00);
    this->writeData(0xC1);
    this->writeData(0x30);

    //DRIVER TIMING CONTROL A
    this->writeCommand(0xE8);
    this->writeData(0x85);
    this->writeData(0x00);
    this->writeData(0x78);

    //DRIVER TIMING CONTROL B
    this->writeCommand(0xEA);
    this->writeData(0x00);
    this->writeData(0x00);

    //POWER ON SEQUENCE CONTROL   ok
    this->writeCommand(0xED);
    this->writeData(0x64);
    this->writeData(0x03);
    this->writeData(0x12);
    this->writeData(0x81);

    //PUMP RATIO CONTROL
    this->writeCommand(0xF7);
    this->writeData(0x20);

    //POWER CONTROL,VRH[5:0]
    this->writeCommand(0xC0); //
    this->writeData(0x23);

    //POWER CONTROL,SAP[2:0];BT[3:0]
    this->writeCommand(0xC1); //
    this->writeData(0x10);

    //VCM CONTROL
    this->writeCommand(0xC5); //
    this->writeData(0x3E);
    this->writeData(0x28);

    //VCM CONTROL 2
    this->writeCommand(0xC7); //
    this->writeData(0x86);

    //MEMORY ACCESS CONTROL
    this->writeCommand(0x36);
    this->writeData(0x48);

    //PIXEL FORMAT
    this->writeCommand(0x3A);
    this->writeData(0x55);

    //FRAME RATIO CONTROL, STANDARD RGB COLOR
    this->writeCommand(0xB1);
    this->writeData(0x00);
    this->writeData(0x18);

    //DISPLAY FUNCTION CONTROL
    this->writeCommand(0xB6);
    this->writeData(0x08);
    this->writeData(0x82);
    this->writeData(0x27);

    //3GAMMA FUNCTION DISABLE
    this->writeCommand(0xF2);
    this->writeData(0x00);

    //GAMMA CURVE SELECTED
    this->writeCommand(0x26);
    this->writeData(0x01);

    //POSITIVE GAMMA CORRECTION
    this->writeCommand(0xE0);
    this->writeData(0x0F);
    this->writeData(0x31);
    this->writeData(0x2B);
    this->writeData(0x0C);
    this->writeData(0x0E);
    this->writeData(0x08);
    this->writeData(0x4E);
    this->writeData(0xF1);
    this->writeData(0x37);
    this->writeData(0x07);
    this->writeData(0x10);
    this->writeData(0x03);
    this->writeData(0x0E);
    this->writeData(0x09);
    this->writeData(0x00);

    //NEGATIVE GAMMA CORRECTION
    this->writeCommand(0xE1);
    this->writeData(0x00);
    this->writeData(0x0E);
    this->writeData(0x14);
    this->writeData(0x03);
    this->writeData(0x11);
    this->writeData(0x07);
    this->writeData(0x31);
    this->writeData(0xC1);
    this->writeData(0x48);
    this->writeData(0x08);
    this->writeData(0x0F);
    this->writeData(0x0C);
    this->writeData(0x31);
    this->writeData(0x36);
    this->writeData(0x0F);

    //EXIT SLEEP
    this->writeCommand(0x11);
    this->delayMs(120);

    //TURN ON DISPLAY
    this->writeCommand(0x29);

    //STARTING ROTATION
    setRotation(Rotation);
    this->flush(0, 0, 40, 40, 0x00ff);
}