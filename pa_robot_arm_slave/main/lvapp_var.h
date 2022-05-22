#ifndef __LVAPP_VAR_H__
#define __LVAPP_VAR_H__

#include "paMods/lvgl-8.2.0/lvgl.h"
struct LvAppVar
{
    lv_obj_t *label1;//限位开关状态
    
    lv_obj_t *label2;//触摸屏状态

    lv_obj_t *label3;//机械臂状态

    lv_obj_t *label_net;//网络状态

    // lv_obj_t *label_robot_arm;
};

#endif // __LVAPP_VAR_H__