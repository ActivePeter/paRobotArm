#include "pa_Main.h"
#ifdef RobotArmApp_demo_Test
//from pa_CommonLib
#include "pa_CommonLib/src/drv/pa_CommonDrv/pa_CommonDrv.h"
#include "pa_CommonLib/src/service/graphic/lvgl/lvgl.h"
#include "pa_CommonLib/src/service/graphic/lvgl/pa_Lvgl/pa_Lvgl.h"
#include "pa_CommonLib/src/util/pa_DataProcessor/pa_DataProcessor.h"
//in project
#include "../GUIs/MainGUI/MainGUI.h"
#include "../GUIs/RobotArmPage/RobotArmPage.h"
#include "../pa_UsedDevice/pa_UsedDevice.h"
#include "../../../RobotArmApp/RobotArmApp.h"

RobotArmApp &robotArm = RobotArmApp::instance;
using namespace pa_UsedDevice;

void tim_100us_tick();
void tim_1ms_tick();
int cnt = 0;
int run = 0;

// int encoder1 = 0;
// int encoder1_delta = 0;
// int encoder2 = 0;
// int encoder2_delta = 0;
// extern TIM_HandleTypeDef htim3, htim4, htim5;
//

namespace TimTasks
{
    bool flag_1s = false;
    void loop()
    {
        if (flag_1s)
        {
            flag_1s = false;
            char buf[20];
            pa_snprintf(buf, 20, "l f: %d %d\r\n", robotArm.getLimitSwitch_LeftArm(), robotArm.getLimitSwitch_RightArm());
            pa_Debug(buf);
            pa_Debug("1s is ticked\r\n");
        }
    }
} // namespace TimTasks

void pa_Main()
{
    pa_setTimerCallback(tim_100us_tick, tim_1ms_tick);
    /*************
     * 
     * screen init
     * 
     * ***********/
    touch.init(240, 320, 210, 3800, 451, 3884, 40);
    ili9341.init(pa_ILI9341::Rotation::Rotation_VERTICAL_2);
    /*************
     * 
     * gui init
     * 
     * ***********/
    lv_init();
    pa_Lvgl_init();
    GUI::initMainGUI();
    /*************
     * 
     * robot arm init
     * 
     * ***********/
    robotArm.init();
    // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, (GPIO_PinState)1);
    run = 0;

    for (;;)
    {

        TimTasks::loop();
        { //lv
            // uint16_t coord[2];
            // pa_touchScreen::instance.readRaw(coord);
            GUI::RobotArmPage_update(robotArm.getLimitSwitch_LeftArm(), robotArm.getLimitSwitch_RightArm());
            GUI::updateEncoder(Global_Touch_X, Global_Touch_Y, run, 1);
            // GUI::updateEncoder(encoder1, encoder1_delta, encoder2, encoder2_delta);
            // GUI::updateAdc(focMotor1.getCurEularAngle());
            lv_task_handler(); //lvgl刷新显示内容
        }
        pa_delayMs(5);

        // HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_1);
    }
}
void tim_100us_tick()
{
    robotArm.onTimerTick();
    // robotArm.onTimerTick();
}
void tim_1ms_tick()
{
    lv_tick_inc(1);
    cnt++;
    if (cnt % 20 == 0)
    {
    }
    if (cnt == 1000)
    {
        cnt = 0;
        TimTasks::flag_1s = true;
        run++;
    }
}
#endif