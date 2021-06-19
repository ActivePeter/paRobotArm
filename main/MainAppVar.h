#ifndef __MAINAPPVAR_H__
#define __MAINAPPVAR_H__
#include "paMods/display/ILI9341/pa_ILI9341.h"
#include "RobotArm/RobotArmApp/RobotArmApp.h"
struct App
{
    pa_ILI9341 lcd;
    RobotArmApp robotArm;
    // Talk talk;
};

extern App app;

#endif // __MAINAPPVAR_H__