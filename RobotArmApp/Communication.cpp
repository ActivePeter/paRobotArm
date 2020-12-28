#include "Communication.h"
#include "RobotArmApp.h"
#include "pa_CommonLib/src/util/transmitData/transmitData.h"
#ifdef STM32_H7
extern "C"
{
#include "usbd_cdc_if.h"
}
#endif

bool RobotArm_Cmd_requesting;
uint64_t lastRequestMs = 0;
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
        // {
        //        if (len == 61)
        {
            RobotArmPoint3D point_p[5];
            memcpy(point_p, data + 1, sizeof(point_p));
            // point_p = (RobotArmPoint3D(*)[5])(data + 1);
            // float a;
            for (int i = 0; i < 5; i++)
            {
                RobotArmApp::instance.pointBuff.addPoint(point_p[i]);
            }
            // RobotArmApp::instance.pointBuff.addPoint((*point_p)[1]);
            // RobotArmApp::instance.pointBuff.addPoint((*point_p)[2]);
            // RobotArmApp::instance.pointBuff.addPoint((*point_p)[3]);
            // RobotArmApp::instance.pointBuff.addPoint((*point_p)[4]);
            // a = (*point_p)[0].x;
            // a = (*point_p)[1].x;
            // a = (*point_p)[2].x;
            // a = (*point_p)[3].x;
            // a = (*point_p)[4].x;
            // a = (*point_p)[4].x;
        }
        break;
        // }
        // RobotArmApp::instance

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

void RobotArm_MsgLoop()
{
    if (pa_millis() - lastRequestMs > 1000)
    {
        RobotArm_Cmd_requesting = false;
    }
    if (!RobotArm_Cmd_requesting)
    {
        if (RobotArmApp::instance.pointBuff.ifNeedSupply())
        {
            RobotArm_Cmd_requesting = true;
            lastRequestMs = pa_millis();
            uint8_t buf[1];
            buf[0] = 0x24;
            RobotArm_Send(buf, 1);
        }
    }
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
