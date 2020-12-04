#include "../MainGUI/MainGUI.h"
#ifdef RobotArmApp_demo_Test

#include "pa_CommonLib/src/service/graphic/lvgl/lvgl.h"

extern "C"
{
#include "stdio.h"
}
#include "pa_CommonLib/src/app/RobotArmApp/RobotStepper/RobotStepper.h"
#include "pa_CommonLib/src/app/RobotArmApp/RobotArmApp/RobotArmApp.h"
#include "pa_CommonLib/src/util/pa_DataProcessor/pa_DataProcessor.h"

namespace GUI
{
    lv_obj_t *robotArmPage;
    lv_obj_t *RobotArmPage_LimitSwitch;
    void dropdown_ChooseDivide(void);
    void switch_MotorEnable(void);

    static void menuBtn_robotArmPage_event_handler(lv_obj_t *obj, lv_event_t event)
    {
        if (event == LV_EVENT_PRESSED)
        {
            switchPage(robotArmPage);
            // lv_obj_set_hidden(curPage, true);
            // lv_obj_set_hidden(menuPage, false);
            // if (lv_obj_is_visible(menuPage))
            // {
            //     lv_obj_set_hidden(menuPage, true);
            // }
            // else
            // {
            //     lv_obj_set_hidden(menuPage, false);
            // }
            // printf("Clicked\n");
        }
    }
    void RobotArmPage_update(char l, char r)
    {
        char buf[20];
        pa_snprintf(buf, 20, "L:%d R:%d", l, r);
        lv_label_set_text(RobotArmPage_LimitSwitch, buf);
    }
    void RobotArmPage_init()
    {
        addMenuBtn(menuBtn_robotArmPage_event_handler, "RobotArm");
        initPage(robotArmPage);
        lv_obj_set_hidden(robotArmPage, true);
        //配置细分度的按键
        dropdown_ChooseDivide();
        //限位开关
        RobotArmPage_LimitSwitch = lv_label_create(robotArmPage, NULL);
        lv_label_set_text(RobotArmPage_LimitSwitch, "l: r:");
        lv_obj_set_pos(RobotArmPage_LimitSwitch, 0, 40);
        //电机开关
        switch_MotorEnable();
    }
    /**************************************
     * 
     * dropdown-细分度
     * 
     * *************************************/
    //选择细分度 回调
    static void dropdown_ChooseDivide_handler(lv_obj_t *obj, lv_event_t event)
    {
        if (event == LV_EVENT_VALUE_CHANGED)
        {
            int id = lv_dropdown_get_selected(obj);
            char buf[30];
            switch (id)
            {
            case 0:
                pa_snprintf(buf, 30, "divide_1 selected\r\n");
                RobotStepper::setDivide(RobotStepper::Divide_a4988_1);
                break;
            case 1:
                pa_snprintf(buf, 30, "divide_2 selected\r\n");
                RobotStepper::setDivide(RobotStepper::Divide_a4988_2);
                break;
            case 2:
                pa_snprintf(buf, 30, "divide_4 selected\r\n");
                RobotStepper::setDivide(RobotStepper::Divide_a4988_4);
                break;
            case 3:
                pa_snprintf(buf, 30, "divide_8 selected\r\n");
                RobotStepper::setDivide(RobotStepper::Divide_a4988_8);
                break;
            case 4:
                pa_snprintf(buf, 30, "divide_16 selected\r\n");
                RobotStepper::setDivide(RobotStepper::Divide_a4988_16);
                break;
            default:
                break;
            }

            pa_Debug(buf);

            // lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
            // printf("Option: %s\n", buf);
        }
    }
    //选择细分度 初始化
    void dropdown_ChooseDivide(void)
    {
        /*Create a normal drop down list*/
        lv_obj_t *ddlist = lv_dropdown_create(robotArmPage, NULL);
        lv_dropdown_set_options(ddlist, "div_1\n"
                                        "div_2\n"
                                        "div_4\n"
                                        "div_8\n"
                                        "div_16");
        lv_dropdown_set_selected(ddlist, 3);

        // lv_obj_align(ddlist, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);
        lv_obj_set_event_cb(ddlist, dropdown_ChooseDivide_handler);
    }
    /**************************************
     * 
     * switch-电机使能
     * 
     * *************************************/
    static void switch_MotorEnable_event(lv_obj_t *obj, lv_event_t event)
    {
        if (event == LV_EVENT_VALUE_CHANGED)
        {
            RobotArmApp::instance.setMotorEnable(lv_switch_get_state(obj));
            // printf("State: %s\n", lv_switch_get_state(obj) ? "On" : "Off");
        }
    }

    void switch_MotorEnable(void)
    {
        /*Create a switch and apply the styles*/
        lv_obj_t *sw1 = lv_switch_create(robotArmPage, NULL);
        // lv_obj_align(sw1, NULL, LV_ALIGN_CENTER, 0, -50);
        lv_obj_set_event_cb(sw1, switch_MotorEnable_event);
        lv_switch_on(sw1, LV_ANIM_ON);
        lv_obj_set_pos(sw1, 140, 2);
        // /*Copy the first switch and turn it ON*/
        // lv_obj_t *sw2 = lv_switch_create(lv_scr_act(), sw1);
        // lv_switch_on(sw2, LV_ANIM_ON);
        // lv_obj_align(sw2, NULL, LV_ALIGN_CENTER, 0, 50);
    }
} // namespace GUI
#endif
