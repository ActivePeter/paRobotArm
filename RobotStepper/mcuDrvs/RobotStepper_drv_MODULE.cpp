#include "../RobotStepper.h"
#include "pa_CommonLib/src/util/pa_DataProcessor/pa_DataProcessor.h"
#ifdef MODULE
//引脚映射函数。没用数组是为了省内存
int RobotStepper_getStepGpioById(char id, GPIO_TypeDef *&port, uint16_t &pin)
{
    // switch (id)
    // {
    // case 0:
    //     port = GPIOD;
    //     pin = GPIO_PIN_0;
    //     break;
    // case 1:
    //     port = GPIOD;
    //     pin = GPIO_PIN_1;
    //     break;
    // case 2:
    //     port = GPIOD;
    //     pin = GPIO_PIN_2;
    //     break;
    // }
}
int RobotStepper_getDirGpioById(char id, GPIO_TypeDef *&port, uint16_t &pin)
{
    // switch (id)
    // {
    // case 0:
    //     port = GPIOD;
    //     pin = GPIO_PIN_3;
    //     break;
    // case 1:
    //     port = GPIOD;
    //     pin = GPIO_PIN_4;
    //     break;
    // case 2:
    //     port = GPIOD;
    //     pin = GPIO_PIN_5;
    //     break;
    // }
}
int RobotStepper_getEnGpioById(char id, GPIO_TypeDef *&port, uint16_t &pin)
{
    // switch (id)
    // {
    // case 0:
    //     port = GPIOD;
    //     pin = GPIO_PIN_6;
    //     break;
    // case 1:
    //     port = GPIOD;
    //     pin = GPIO_PIN_7;
    //     break;
    // case 2:
    //     port = GPIOC;
    //     pin = GPIO_PIN_12;
    //     break;
    // }
}
void RobotStepper::setStepPin(char state)
{
    // GPIO_TypeDef *gpio;
    // uint16_t pin;
    // RobotStepper_getStepGpioById(this->id, gpio, pin);
    // HAL_GPIO_WritePin(gpio, pin, (GPIO_PinState)state);
}
void RobotStepper::setDirPin(char state)
{
    // GPIO_TypeDef *gpio;
    // uint16_t pin;
    // RobotStepper_getDirGpioById(this->id, gpio, pin);
    // HAL_GPIO_WritePin(gpio, pin, (GPIO_PinState)state);
}
void RobotStepper::setEnPin(char state)
{
    // GPIO_TypeDef *gpio;
    // uint16_t pin;
    // RobotStepper_getEnGpioById(this->id, gpio, pin);
    // HAL_GPIO_WritePin(gpio, pin, (GPIO_PinState)state);
    // // {
    // //     char buf[20];
    // //     pa_snprintf(buf, 20, "%x\r\n\r\n", (uint32_t)gpio);
    // //     pa_Debug(buf);
    // // }
}
void RobotStepper::setDividePin(bool ms1, bool ms2, bool ms3)
{
}
#endif