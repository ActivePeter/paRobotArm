#include "lvapp.h"

// #include "MainApp.c.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
#include "paCoreInc/all"
// #include "paMods/display/ILI9341/pa_ILI9341.h"
#include "paMods/lvgl-8.2.0/lvgl.h"
#include "app_var.h"
#include "communication.h"

#define MY_DISP_HOR_RES 240
#define MY_DISP_VER_RES 320
namespace check_state
{
    void sw_robot_arm_motor_en(lv_obj_t* obj,bool send){
        appVar.robotArm.setMotorEnable(lv_obj_has_state(obj, LV_STATE_CHECKED));
        if(send){
            auto pack=communication::Packs::Pack_SwitchMotorEn(appVar.robotArm.getMotorEnable());
            Serial.printf("%d %d %d\n",
                pack.switch_en,
                lv_obj_has_state(obj, LV_STATE_CHECKED),
                appVar.robotArm.getMotorEnable());
            communication::send::send_data(
                communication::PackIds::SwitchMotorEn,
                pack
            );
        }
    }
}
namespace callback
{
    void palv_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
    {
        int32_t bufSize = (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1);
        // /*It's a very slow but simple implementation.
        //  *`set_pixel` needs to be written by you to a set pixel on the screen*/
        // tft.startWrite();
        // tft.setAddrWindow(area->x1,
        //                   area->y1,
        //                   area->x2 - area->x1,
        //                   area->y2 - area->y1);
        // tft.writePixels((uint16_t *)color_p, bufSize);
        // tft.endWrite();
        appVar.lcd.setAddress(area->x1, area->y1, area->x2, area->y2);
        appVar.lcd.transmitBuf((uint8_t *)color_p, bufSize * 2);
        // appVar.lcd.flush(area->x1, area->y1, area->x2, area->y2, 0xff00);
        // _G_paBase.output("hello my_disp_flush\r\n");
        // for (y = area->y1; y <= area->y2; y++)
        // {
        //     for (x = area->x1; x <= area->x2; x++)
        //     {
        //         set_pixel(x, y, *color_p);
        //         color_p++;
        //     }
        // }

        // tft.drawRGBBitmap(area->x1,
        //                   area->y1, (uint16_t *)color_p,
        //                   area->x2 - area->x1 + 1, area->y2 - area->y1 + 1);

        lv_disp_flush_ready(disp); /* Indicate you are ready with the flushing*/
    }
    void my_input_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
    {
        auto &pi = appVar.pointer_info;
        pi.down = appVar.xpt2046.isPressed();
        //触摸屏数据
        uint16_t raw[2];
        auto succ = appVar.xpt2046.readRaw(raw);
        if (!succ)
        {
            pi.down = 0;
        }
        pi.raw_x = raw[0];
        pi.raw_y = raw[1];
        appVar.xpt2046.turnRawToScreen(raw);
        pi.x = raw[0];
        pi.y = raw[1];
        if (pi.down)
        {
            data->point.x = pi.y;
            data->point.y = pi.x;
            data->state = LV_INDEV_STATE_PRESSED;
        }
        else
        {
            data->state = LV_INDEV_STATE_RELEASED;
        }
    }
    void robot_switch_event_handler(lv_event_t *e)
    {
        lv_event_code_t code = lv_event_get_code(e);
        lv_obj_t *obj = lv_event_get_target(e);
        if (code == LV_EVENT_VALUE_CHANGED)
        {
            check_state::sw_robot_arm_motor_en(obj,true);
            // LV_LOG_USER("State: %s\n", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "On" : "Off");
        }
    }
}
lv_disp_drv_t disp_drv;
void lv_app_init()
{
    { //显示缓冲
        /*A static or global variable to store the buffers*/
        static lv_disp_draw_buf_t disp_buf;

        /*Static or global buffer(s). The second buffer is optional*/
        static lv_color_t buf_1[MY_DISP_HOR_RES * 10];
        static lv_color_t buf_2[MY_DISP_HOR_RES * 10];

        /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
        lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, MY_DISP_HOR_RES * 10);

        static lv_disp_drv_t disp_drv;                 /*A variable to hold the drivers. Must be static or global.*/
        lv_disp_drv_init(&disp_drv);                   /*Basic initialization*/
        disp_drv.draw_buf = &disp_buf;                 /*Set an initialized buffer*/
        disp_drv.flush_cb = callback::palv_disp_flush; /*Set a flush callback to draw to the display*/
        disp_drv.hor_res = 320;                        /*Set the horizontal resolution in pixels*/
        disp_drv.ver_res = 240;                        /*Set the vertical resolution in pixels*/

        lv_disp_t *disp;
        disp = lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/
    }
    { //输入设备
        static lv_indev_drv_t indev_drv;
        lv_indev_drv_init(&indev_drv); /*Basic initialization*/
        indev_drv.type = LV_INDEV_TYPE_POINTER;
        indev_drv.read_cb = callback::my_input_read;
        /*Register the driver in LVGL and save the created input device object*/
        lv_indev_t *my_indev = lv_indev_drv_register(&indev_drv);
    }
}

static void anim_x_cb(void *var, int32_t v)
{
    lv_obj_set_x((lv_obj_t *)var, v);
}

static void anim_size_cb(void *var, int32_t v)
{
    lv_obj_set_size((lv_obj_t *)var, v, v);
}

/**
 * Create a playback animation
 */
void lv_example_anim_2(void)
{

    lv_obj_t *obj = lv_obj_create(lv_scr_act());
    lv_obj_set_style_bg_color(obj, lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_set_style_radius(obj, LV_RADIUS_CIRCLE, 0);

    lv_obj_align(obj, LV_ALIGN_LEFT_MID, 10, 0);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_values(&a, 10, 50);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_playback_delay(&a, 100);
    lv_anim_set_playback_time(&a, 300);
    lv_anim_set_repeat_delay(&a, 500);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);

    lv_anim_set_exec_cb(&a, anim_size_cb);
    lv_anim_start(&a);
    lv_anim_set_exec_cb(&a, anim_x_cb);
    lv_anim_set_values(&a, 10, 240);
    lv_anim_start(&a);
}

namespace lvapp
{
    void init_all_gui()
    {
        /*Create a container with COLUMN flex direction*/
        lv_obj_t *cont_col = lv_obj_create(lv_scr_act());
        lv_obj_set_size(cont_col, 300, 220);
        lv_obj_set_pos(cont_col, 10, 10);
        lv_obj_set_flex_flow(cont_col, LV_FLEX_FLOW_COLUMN);

        //测试文本
        appVar.lvapp_var.label1 =
            // lv_obj_t *label1
            lv_label_create(cont_col);
        appVar.lvapp_var.label2 =
            // lv_obj_t *label1
            lv_label_create(cont_col);
        appVar.lvapp_var.label3 =
            // lv_obj_t *label1
            lv_label_create(cont_col);
        appVar.lvapp_var.label_net =
            // lv_obj_t *label1
            lv_label_create(cont_col);
        // appVar.lvapp_var.label_robot_arm =
            // lv_label_create(cont_col);

        lv_label_set_text(appVar.lvapp_var.label1, "test");
        lv_label_set_text(appVar.lvapp_var.label2, "test");
        lv_label_set_text(appVar.lvapp_var.label3, "test");
        lv_label_set_text(appVar.lvapp_var.label_net, "test");

        //开关
        lv_obj_t *sw = lv_switch_create(cont_col);
        appVar.lvapp_var.sw_robot_arm_motor_en=sw;
        lv_obj_add_event_cb(sw, callback::robot_switch_event_handler, LV_EVENT_ALL, NULL);
    }
    void update_limit_btn_state(
        bool limit1, bool limit2)
    {
        char buf[100];
        sprintf(buf, "limit 1:%d 2:%d",
                limit1, limit2);
        lv_label_set_text(appVar.lvapp_var.label1, buf);
    }
    void update_xpt_2046_state()
    {
        char buf[100];
        auto &pi = appVar.pointer_info;
        sprintf(buf, "touch raw:%4d %4d final:%4d %4d\ndown:%s",
                pi.raw_x, pi.raw_y,
                pi.x, pi.y, pi.down ? "true" : "false");
        lv_label_set_text(appVar.lvapp_var.label2, buf);
    }
    void update_recent_cmd_pos()
    {
        char buf[100];
        auto &pi = appVar.pointer_info;
        sprintf(buf, "recent cmd pos:%4d %4d",
                appVar.recent_cmd_pos.x,
                appVar.recent_cmd_pos.y);
        lv_label_set_text(appVar.lvapp_var.label3, buf);
    }
    void update_robot_arm_state(){
        char buf[100];
        auto &pi = appVar.pointer_info;
        sprintf(buf, "robot arm motor:%s",
                appVar.robotArm.getMode()==RobotArmApp::mode_idle?"disable":"enable");
        lv_label_set_text(appVar.lvapp_var.label3, buf);
    }
    void update_net_state(){
        char buf[100];
        sprintf(buf, "net wifi:%s \n    host:%s",
                appVar.wifi_state.connected?"connected":"disconnected",
                appVar.tcp_client.connected?"connected":"disconnected");

        lv_label_set_text(appVar.lvapp_var.label_net, buf);
    }
    void set_robot_arm_motor_en_switch(bool en){
        if(en){
            lv_obj_add_state(appVar.lvapp_var.sw_robot_arm_motor_en,
                            LV_STATE_CHECKED);
        }else{
            lv_obj_clear_state(appVar.lvapp_var.sw_robot_arm_motor_en,
                            LV_STATE_CHECKED);
        }
        check_state::sw_robot_arm_motor_en(
            appVar.lvapp_var.sw_robot_arm_motor_en,false);
    }
    void tick_update()
    {
        //限位开关数据
        update_limit_btn_state(
            appVar.robotArm.getLimitSwitch_LeftArm(),
            appVar.robotArm.getLimitSwitch_RightArm());
        update_xpt_2046_state();
        update_robot_arm_state();
        update_net_state();

        lv_timer_handler();
    }
}