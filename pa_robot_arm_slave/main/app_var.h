#ifndef __APP_VAR_H__
#define __APP_VAR_H__
#include "paMods/display/ILI9341/pa_ILI9341.h"
#include "robot/RobotArmApp/RobotArmApp.h"
#include "lvapp_var.h"
#include "paMods/input/xpt2046/pa_xpt2046.h"
#include "platform_impl/wifi_impl.h"
#include "platform_impl/tcpclient.h"

struct PointerInfo{
    uint16_t x;
    uint16_t y;
    uint16_t raw_x;
    uint16_t raw_y;
    uint8_t down;
};
struct RecentCmdPos{
    int x;
    int y;
};
struct AppVar
{
    pa_ILI9341 lcd;
    pa_Xpt2046 xpt2046;
    RobotArmApp robotArm;
    LvAppVar lvapp_var;
    PointerInfo pointer_info;
    WifiState wifi_state;
    TcpClient tcp_client;
    RecentCmdPos recent_cmd_pos;
    // Talk talk;
};
extern AppVar appVar;

#endif // __APP_VAR_H__