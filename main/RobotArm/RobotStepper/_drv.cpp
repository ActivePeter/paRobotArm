#include "RobotStepper.h"
#include "../_drv_inc.h"

void RobotStepper::setStepPin(char state)
{
    switch (id)
    {
    case 0:
        _G_paGPIO.write(RobotArm_GPIO_Step0, state);
        break;
    case 1:
        _G_paGPIO.write(RobotArm_GPIO_Step1, state);
        break;
    case 2:
        _G_paGPIO.write(RobotArm_GPIO_Step2, state);
        break;
    default:
        break;
    }
}

void RobotStepper::setDirPin(char dir)
{
    switch (id)
    {
    case 0:
        _G_paGPIO.write(RobotArm_GPIO_Dir0, dir);
        break;
    case 1:
        _G_paGPIO.write(RobotArm_GPIO_Dir1, dir);
        break;
    case 2:
        _G_paGPIO.write(RobotArm_GPIO_Dir2, dir);
        break;
    default:
        break;
    }
}

void RobotStepper::setEnPin(char state)
{
    switch (id)
    {
    case 0:
        _G_paGPIO.write(RobotArm_GPIO_En0, state);
        break;
    case 1:
        _G_paGPIO.write(RobotArm_GPIO_En1, state);
        break;
    case 2:
        _G_paGPIO.write(RobotArm_GPIO_En2, state);
        break;
    default:
        break;
    }
}

#ifdef RobotStepper_Use_A4988
void RobotStepper::setDividePin(bool ms1, bool ms2, bool ms3)
{
    _G_paGPIO.write(RobotArm_GPIO_MS1, ms1);
    _G_paGPIO.write(RobotArm_GPIO_MS2, ms2);
    _G_paGPIO.write(RobotArm_GPIO_MS3, ms3);
}
#endif
void RobotStepper::initHardware()
{
    static bool inited = false;

    if (!inited)
    {
        _G_paGPIO.init(N_paGPIO::Mode_Output, RobotArm_GPIO_Dir0);
        _G_paGPIO.init(N_paGPIO::Mode_Output, RobotArm_GPIO_Dir1);
        _G_paGPIO.init(N_paGPIO::Mode_Output, RobotArm_GPIO_Dir2);

        _G_paGPIO.init(N_paGPIO::Mode_Output, RobotArm_GPIO_En0);
        _G_paGPIO.init(N_paGPIO::Mode_Output, RobotArm_GPIO_En1);
        _G_paGPIO.init(N_paGPIO::Mode_Output, RobotArm_GPIO_En2);

        _G_paGPIO.init(N_paGPIO::Mode_Output, RobotArm_GPIO_MS1);
        _G_paGPIO.init(N_paGPIO::Mode_Output, RobotArm_GPIO_MS2);
        _G_paGPIO.init(N_paGPIO::Mode_Output, RobotArm_GPIO_MS3);

        _G_paGPIO.init(N_paGPIO::Mode_Output, RobotArm_GPIO_Step0);
        _G_paGPIO.init(N_paGPIO::Mode_Output, RobotArm_GPIO_Step1);
        _G_paGPIO.init(N_paGPIO::Mode_Output, RobotArm_GPIO_Step2);

        inited = true;
    }
}
