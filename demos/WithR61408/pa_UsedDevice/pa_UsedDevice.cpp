
#include "pa_UsedDevice.h"
#ifdef RobotArmApp_demo_WithR61408
namespace pa_UsedDevice
{
    pa_ILI9341 &ili9341 = pa_ILI9341::instance;
    pa_touchScreen &touch = pa_touchScreen::instance;
} // namespace pa_UsedDevice
#endif