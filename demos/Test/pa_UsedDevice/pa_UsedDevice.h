#include "pa_Defines.h"
#ifdef RobotArmApp_demo_Test

#ifndef __PA_USEDDEVICE_H__
#define __PA_USEDDEVICE_H__

#include "pa_CommonLib/src/app/SvpwmFoc/SvpwmFoc.h"
#include "pa_CommonLib/src/service/input/touchScreen/pa_touchScreen.h"
#include "pa_CommonLib/src/service/TI_Chips/Ads_112c04/Ads_112c04.h"
#include "pa_CommonLib/src/service/display/ili9341/pa_ILI9341.h"

#include "pa_CommonLib/src/service/sensors/attitude/AS5048A/AS5048A.h"

namespace pa_UsedDevice
{
    extern pa_ILI9341 &ili9341;
    extern pa_touchScreen &touch;
} // namespace pa_UsedDevice

#endif // __PA_USEDDEVICE_H__
#endif