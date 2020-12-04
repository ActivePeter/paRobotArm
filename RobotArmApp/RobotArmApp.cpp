#include "RobotArmApp.h"
#include "pa_CommonLib/src/drv/pa_PWM/pa_PWM.h"
RobotArmApp RobotArmApp::instance = RobotArmApp();
RobotArmApp::RobotArmApp() {}

void RobotArmApp::onTimerTick()
{
    pinStateOnBackupMode = !pinStateOnBackupMode;
    for (int i = 0; i < 3; i++)
    {
        doStepperEvent(robotSteppers[i]);
    }
    switch (curMode)
    {
    case Mode::mode_backup:

        break;
    case Mode::mode_running:
        if (currentTick == tickCountInOneMove)
        {
            prepareNextMove();
        }
        currentTick++;
        break;
    default:
        break;
    }
}

void RobotArmApp::setMode(Mode mode)
{
    curMode = mode;
}

void RobotArmApp::init()
{
    for (int i = 0; i < 3; i++)
    {
        robotSteppers[i].setId(i);
        robotSteppers[i].setEnPin(0);
    }
#ifdef RobotStepper_Use_A4988
    RobotStepper::setDivide(RobotStepper::Divide_a4988_8);
#endif
}

void RobotArmApp::setMotorEnable(char enable)
{
    for (int i = 0; i < 3; i++)
    {
        robotSteppers[i].setEnPin(!enable);
    }
}
//一段路程切片走完后准备下一段路径
void RobotArmApp::prepareNextMove()
{
    //tick计数清0
    currentTick = 0;
    //先赋值下一次步进完成所需要的时间 tickCountInOneMove
    this->tickCountInOneMove = 1;

    for (int i = 0; i < 3; i++)
    {
        //步进值计数复位  stepper.curStepInOneMove;
        robotSteppers[i].curStepInOneMove = 0;
        //然后计算三个步进所需要的步进数 stepper.totalStepInOneMove
        calcAndSetStep(robotSteppers[i]);
    }

    //设置三个步进的步进方向
}

void RobotArmApp::doStepperEvent(RobotStepper &stepper)
{

    switch (curMode)
    {
    case Mode::mode_backup:
        switch (stepper.getId())
        {
        case 0:
            if (!getLimitSwitch_LeftArm())
            {
                stepper.setStepPin((char)pinStateOnBackupMode);
            }
            break;
        case 1:
            // if (!getLimitSwitch_RightArm())
            {
                stepper.setStepPin((char)pinStateOnBackupMode);
                // pinStateOnBackupMode = !pinStateOnBackupMode;
            }
            break;
        default:
            break;
        }

        break;
    case Mode::mode_running:
        if (stepper.curStepInOneMove != stepper.totalStepInOneMove)
        {
            //当前tick帧是否为脉冲上升帧
            if (currentTick == (tickCountInOneMove - 1) * stepper.curStepInOneMove / stepper.totalStepInOneMove)
            {
                stepper.setStepPin(1);
                stepper.curStepInOneMove++;
            }
            else
            {
                stepper.setStepPin(0);
            }
        }
        break;
    }
}

void RobotArmApp::calcAndSetStep(RobotStepper &stepper)
{
    switch (stepper.getId())
    {
    case 1:

        break;
    }
    //根据stepper的id来计算对应的步进值
    int step;
    stepper.setDirPin(step > 0);
    stepper.totalStepInOneMove = step > 0 ? step : -step;
}
