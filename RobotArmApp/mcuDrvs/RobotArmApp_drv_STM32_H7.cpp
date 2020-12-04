#include "../RobotArmApp.h"
#include "pa_CommonLib/src/util/pa_DataProcessor/pa_DataProcessor.h"
#ifdef STM32_H7

#define RobotArmApp_LimitSwitch_LeftArm_Port GPIOE
#define RobotArmApp_LimitSwitch_LeftArm_Pin GPIO_PIN_5

#define RobotArmApp_LimitSwitch_RightArm_Port GPIOE
#define RobotArmApp_LimitSwitch_RightArm_Pin GPIO_PIN_6

char RobotArmApp::getLimitSwitch_LeftArm()
{
    HAL_GPIO_ReadPin(RobotArmApp_LimitSwitch_LeftArm_Port, RobotArmApp_LimitSwitch_LeftArm_Pin);
}

char RobotArmApp::getLimitSwitch_RightArm()
{
    HAL_GPIO_ReadPin(RobotArmApp_LimitSwitch_RightArm_Port, RobotArmApp_LimitSwitch_RightArm_Pin);
}

#endif