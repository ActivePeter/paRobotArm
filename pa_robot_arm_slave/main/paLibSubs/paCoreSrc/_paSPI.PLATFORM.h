#ifndef ___PASPI_PLATFORM_H__
#define ___PASPI_PLATFORM_H__

#include "Conf_platform.h"

#if PLATFORM_ESP32
#define PASPI_HOST HSPI_HOST //hspi

#define PIN_NUM_MISO 25
#define PIN_NUM_MOSI 23
#define PIN_NUM_CLK 19
#define PIN_NUM_CS 22

// #define PIN_NUM_DC 21
// #define PIN_NUM_RST 18
// #define PIN_NUM_BCKL 5
#elif PLATFORM_ESP32_S2
#define PASPI_HOST SPI2_HOST //vspi

#define PIN_NUM_MISO 37
#define PIN_NUM_MOSI 35
#define PIN_NUM_CLK 36
#define PIN_NUM_CS 34

// #define PIN_NUM_DC 4
// #define PIN_NUM_RST 5
// #define PIN_NUM_BCKL 6
#elif PLATFORM_ESP32_C3
#define PASPI_HOST SPI2_HOST //vspi

#define PIN_NUM_MISO 2
#define PIN_NUM_MOSI 7
#define PIN_NUM_CLK 6
#define PIN_NUM_CS 10

// #define PIN_NUM_DC 9
// #define PIN_NUM_RST 4
// #define PIN_NUM_BCKL 5
#endif
#endif // ___PASPI.PLATFORM_H__