#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__
#include "stdint.h"

typedef enum
{
    RobotArm_Cmd_NA,
    RobotArm_Cmd_Start,
    RobotArm_Cmd_Stop,
    RobotArm_Cmd_AddPoints,
} RobotArm_Cmd;

#ifdef __cplusplus
extern "C"
{
#endif
    void RobotArm_HandleReceiveMsg(uint8_t *data, uint32_t len);
#ifdef __cplusplus
}
#endif
// void RobotArm_Send(uint8_t *Buf, uint16_t Len);
void RobotArm_MsgLoop();

#endif // __COMMUNICATION_H__