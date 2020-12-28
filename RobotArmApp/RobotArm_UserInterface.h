#ifndef __ROBOTARM_GUIINTERFACE_H__
#define __ROBOTARM_GUIINTERFACE_H__
// #include "RobotArmApp.h"
class RobotArmApp;
// class RobotArmModel;
class RobotArm_UserInterface
{
public:
    RobotArm_UserInterface();

    void setMotorEnable_do(char enable);
    void setMotorEnable_setGuiCallback(void (*callback)(char enable));

private:
    // RobotArmApp &robotArm; //= RobotArmApp::instance;
    void (*setMotorEnable_guiCallback)(char enable);
};

#endif // __ROBOTARM_GUIINTERFACE_H__