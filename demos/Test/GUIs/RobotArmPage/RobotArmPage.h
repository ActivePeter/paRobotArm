#ifndef __ROBOTARMPAGE_H__
#define __ROBOTARMPAGE_H__

#include "pa_Defines.h"
#ifdef RobotArmApp_demo_Test
#include "../MainGUI/MainGUI.h"
namespace GUI
{
    void RobotArmPage_init();
    void RobotArmPage_update(char l, char r);
} // namespace GUI
#endif // __MAINGUI_H__

#endif // __ROBOTARMPAGE_H__