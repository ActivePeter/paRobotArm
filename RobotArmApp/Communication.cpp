#include "Communication.h"
#include "RobotArmApp.h"
#ifdef STM32_H7
extern "C"
{
#include "usbd_cdc_if.h"
}
#endif
RobotArm_Cmd RobotArm_judgeCmd(uint8_t data);
//this func should be called in receive callback;
void RobotArm_HandleReceiveMsg(uint8_t *data, uint32_t len)
{

    switch (RobotArm_judgeCmd(data[0]))
    {
    case RobotArm_Cmd_Start:
        RobotArmApp::instance.userInterface.setMotorEnable_do(1);
        break;
    case RobotArm_Cmd_Stop:
        RobotArmApp::instance.userInterface.setMotorEnable_do(0);
        break;
    case RobotArm_Cmd_AddPoints:
        RobotArmApp::instance
        break;
    default:
        break;
    }
}

void RobotArm_Send(uint8_t *Buf, uint16_t Len)
{
#ifdef STM32_H7
    while (CDC_Transmit_FS(Buf, Len))
        ;
#endif
}

RobotArm_Cmd RobotArm_judgeCmd(uint8_t data)
{
    switch (data)
    {
    case 0x21:
        return RobotArm_Cmd_Start;
        break;
    case 0x22:
        return RobotArm_Cmd_Stop;
        break;
    case 0x23:
        return RobotArm_Cmd_AddPoints;
    default:
        return RobotArm_Cmd_NA;
        break;
    }
}
