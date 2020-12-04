#ifndef __MAINGUI_H__
#define __MAINGUI_H__

#include "pa_Defines.h"
#ifdef RobotArmApp_demo_Test

#include "pa_CommonLib/src/service/graphic/lvgl/lvgl.h"
namespace GUI
{
    void initMainGUI();
    void updateRuningTime(int time);
    void updateEncoder(int E1, int E1_d, int E2, int E2_d);
    void updateAdc(double value);
    void addMenuBtn(lv_event_cb_t pressEventHandler, const char *text);
    void switchPage(lv_obj_t *page);
    void initPage(lv_obj_t *&page);
} // namespace GUI
#endif // __MAINGUI_H__

#endif