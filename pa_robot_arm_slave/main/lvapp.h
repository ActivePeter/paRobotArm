#ifndef __LVAPP_H__
#define __LVAPP_H__
#include "paMods/display/ILI9341/pa_ILI9341.h"
#include "paMods/lvgl-8.2.0/lvgl.h"

void lv_app_init();
void lv_example_anim_2(void);
namespace lvapp
{
    void init_all_gui();
    void tick_update();
    void update_recent_cmd_pos();
    void set_robot_arm_motor_en_switch(bool en);
}

#endif // __LVAPP_H__