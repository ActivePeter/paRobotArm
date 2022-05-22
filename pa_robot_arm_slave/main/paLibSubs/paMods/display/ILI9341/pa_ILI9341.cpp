#include "pa_ILI9341.h"

void pa_ILI9341::reset()
{
	this->setRST(0);
	// HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
	this->delayMs(200);
	// delayMs(200);
	this->setCS(0);
	// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	this->delayMs(200);
	// delayMs(200);
	this->setRST(1);
	// HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
}

void pa_ILI9341::enable()
{
	this->setRST(1);
	// setCS(1);
	// setDC(1);
	// int i = 0;
	// while (1)
	// {
	// 	i++;
	// 	delayMs(1);
	// }
}

void pa_ILI9341::flush(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Colour)
{
	if (x1 < 0)
		x1 = 0;
	if (y1 < 0)
		y1 = 0;
	if (x2 > this->LCD_WIDTH)
		x2 = LCD_WIDTH;
	if (y2 > this->LCD_HEIGHT)
		y2 = LCD_HEIGHT;
	setAddress(x1, y1, x2, y2);
	burst(Colour, (x2 - x1 + 1) * (y2 - y1 + 1));
}

void pa_ILI9341::burst(uint16_t Colour, uint32_t Size)
{
	//SENDS COLOUR
	uint32_t Buffer_Size = 0;
	if ((Size * 2) < BURST_MAX_SIZE)
	{
		Buffer_Size = Size;
	}
	else
	{
		Buffer_Size = BURST_MAX_SIZE;
	}

	setDC(1);
	setCS(0);
	// HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);

	unsigned char chifted = Colour >> 8;
	;
	//=new unsigned char[Buffer_Size];
	for (uint32_t j = 0; j < Buffer_Size; j += 2)
	{
		pa_ILI9341_burst_buffer[j] = chifted;
		pa_ILI9341_burst_buffer[j + 1] = Colour;
	}

	uint32_t Sending_Size = Size * 2;
	uint32_t Sending_in_Block = Sending_Size / Buffer_Size;
	uint32_t Remainder_from_block = Sending_Size % Buffer_Size;

	if (Sending_in_Block != 0)
	{
		for (uint32_t j = 0; j < (Sending_in_Block); j++)
		{
			transmit(spiId, pa_ILI9341_burst_buffer, Buffer_Size);
			// HAL_SPI_Transmit(HSPI_INSTANCE, (unsigned char *)burst_buffer, Buffer_Size, 10);
		}
	}

	transmit(spiId, pa_ILI9341_burst_buffer, Remainder_from_block);
	//REMAINDER!
	// HAL_SPI_Transmit(HSPI_INSTANCE, (unsigned char *)burst_buffer, Remainder_from_block, 10);

	setCS(1);
	// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void pa_ILI9341::writeCommand(uint8_t Command)
{
	this->setCS(0);
	this->setDC(0);
	transmit(spiId, &Command, 1);
	this->setCS(1);
	// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
	// ILI9341_SPI_Send(Command);
	// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void pa_ILI9341::writeData(uint8_t Command)
{
	this->setDC(1);
	this->setCS(0);
	transmit(spiId, &Command, 1);
	this->setCS(1);
	// HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	// ILI9341_SPI_Send(Data);
	// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void pa_ILI9341::setAddress(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
	if (X1 < 0)
		X1 = 0;
	if (Y1 < 0)
		Y1 = 0;
	if (X2 > this->LCD_WIDTH)
		X2 = LCD_WIDTH;
	if (Y2 > this->LCD_HEIGHT)
		Y2 = LCD_HEIGHT;

	this->writeCommand(0x2A);
	this->writeData(X1 >> 8);
	this->writeData(X1);
	this->writeData(X2 >> 8);
	this->writeData(X2);

	this->writeCommand(0x2B);
	this->writeData(Y1 >> 8);
	this->writeData(Y1);
	this->writeData(Y2 >> 8);
	this->writeData(Y2);

	this->writeCommand(0x2C);
}

void pa_ILI9341::setRotation(Rotation Rotation)
{
	// uint8_t screen_rotation = Rotation;

	this->writeCommand(0x36);
	delayMs(1);

	switch (Rotation)
	{
	case Rotation_VERTICAL_1:
		this->writeData(0x40 | 0x08);
		LCD_WIDTH = 240;
		LCD_HEIGHT = 320;
		break;
	case Rotation_HORIZONTAL_1:
		this->writeData(0x20 | 0x08);
		LCD_WIDTH = 320;
		LCD_HEIGHT = 240;
		break;
	case Rotation_VERTICAL_2:
		this->writeData(0x80 | 0x08);
		LCD_WIDTH = 240;
		LCD_HEIGHT = 320;
		break;
	case Rotation_HORIZONTAL_2:
		this->writeData(0x40 | 0x80 | 0x20 | 0x08);
		LCD_WIDTH = 320;
		LCD_HEIGHT = 240;
		break;
	default:
		//EXIT IF SCREEN ROTATION NOT VALID!
		break;
	}
}
