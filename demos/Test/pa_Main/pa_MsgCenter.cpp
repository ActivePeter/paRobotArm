#include "pa_MsgCenter.h"

#ifdef RobotArmApp_demo_Test
#include "pa_CommonLib/src/app/RobotArmApp/RobotArmApp/Communication.h"

void pa_MsgCenterThread(void const *argument);
void pa_MsgCenter_initThread()
{
  osThreadDef(defaultTask, pa_MsgCenterThread, osPriorityNormal, 0, 6000);
  osThreadCreate(osThread(defaultTask), NULL);
}
extern uint8_t UserRxBufferFS[];
uint32_t pa_MsgCenterBuffHandled_Len = 0;
void pa_MsgCenterThread(void const *argument)
{
  for (;;)
  {

    if (pa_MsgCenterBuffHandled_Len)
    {
      RobotArm_HandleReceiveMsg(UserRxBufferFS, pa_MsgCenterBuffHandled_Len);
      pa_MsgCenterBuffHandled_Len = 0;
    }

    osDelay(1);
  }
}
#endif