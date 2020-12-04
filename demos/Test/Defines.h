#ifndef __DEFINES_H__
#define __DEFINES_H__

/***********************************************
 * 
 * 
 * 显示器外设选择宏
 * 
 * 
 * **********************************************/
#ifndef DISPLAY_USE_ILI9341
#define DISPLAY_USE_ILI9341
#endif

// #ifndef DISPLAY_USE_SSD1306
// #define DISPLAY_USE_SSD1306
// #endif

// #ifndef DISPLAY_USE_ST7789
// #define DISPLAY_USE_ST7789
// #endif

/***********************************************
 * 
 * 
 * 图形库选择宏
 * 
 * 
 * **********************************************/

#ifndef GRAPHIC_USE_LVGL
#define GRAPHIC_USE_LVGL
#endif

/***********************************************
 * 
 * 
 * 输入外设选择宏
 * 
 * 
 * **********************************************/
// #ifndef INPUT_USE_KEYPAD
// #define INPUT_USE_KEYPAD
// #endif

#ifndef INPUT_USE_TOUCHSCREEN
#define INPUT_USE_TOUCHSCREEN
#endif

/***********************************************
 * 
 * 
 * 输入外设选择宏
 * 
 * 
 * **********************************************/

#define pa_MEM_CUSTOM_INCLUDE "FreeRTOS.h" /*Header for the dynamic memory function*/
#define pa_MEM_CUSTOM_ALLOC pvPortMalloc   /*Wrapper to malloc*/
#define pa_MEM_CUSTOM_FREE vPortFree       /*Wrapper to free*/

#endif // __DEFINES_H__