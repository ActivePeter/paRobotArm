#include "RobotArmApp.h"
#include "pa_CommonLib/src/drv/pa_PWM/pa_PWM.h"
RobotArmApp RobotArmApp::instance = RobotArmApp();
RobotArmApp::RobotArmApp() {}

void RobotArmApp::onTimerTick()
{
    switch (curMode)
    {
    case Mode::mode_backup:
        pinStateOnBackupMode = !pinStateOnBackupMode;
        for (int i = 0; i < 3; i++)
        {
            doStepperEvent(robotSteppers[i]);
        }
        break;
    case Mode::mode_running:
        for (int i = 0; i < 3; i++)
        {
            doStepperEvent(robotSteppers[i]);
        }
        // if (currentTick == tickCountInOneMove)
        // {
        //     prepareNextMove();
        // }
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
    robotSteppers[0].init(0, RobotArmStepper1_Inverted);
    robotSteppers[1].init(0, RobotArmStepper2_Inverted);
    robotSteppers[2].init(0, RobotArmStepper3_Inverted);
#ifdef RobotStepper_Use_A4988
    RobotStepper::setDivide(RobotStepper::divide_a4988_8);
#endif
}

void RobotArmApp::setMotorEnable(char enable)
{
    if (!enable)
    {
        this->curMode = Mode::mode_backup;
    }
    for (int i = 0; i < 3; i++)
    {
        robotSteppers[i].setEnPin(!enable);
    }
}

/***************************
 * 
 *      主要执行代码
 * 
 * *************************/
void RobotArmApp::doStepperEvent(RobotStepper &stepper)
{

    switch (curMode)
    {
    //复位模式
    case Mode::mode_backup:
    {
        static uint16_t limitSwitchActivatedCnt_LeftArm = 0;
        static uint16_t limitSwitchActivatedCnt_RightArm = 0;
        switch (stepper.getId())
        {
        case 0:
            if (!getLimitSwitch_LeftArm())
            {
                limitSwitchActivatedCnt_LeftArm = 0;
                stepper.setStepPin((char)pinStateOnBackupMode);
            }
            else if (limitSwitchActivatedCnt_LeftArm < limitSwitchActivatedCnt_MAX)
            {
                limitSwitchActivatedCnt_LeftArm++;
            }
            break;
        case 1:
            if (!getLimitSwitch_RightArm())
            {
                stepper.setStepPin((char)pinStateOnBackupMode);
                // pinStateOnBackupMode = !pinStateOnBackupMode;
            }
            break;
        default:
            break;
        }
        //全部已经复位的条件满足后
        if (limitSwitchActivatedCnt_LeftArm == limitSwitchActivatedCnt_MAX)
        {
            curMode = Mode::mode_running;
            for (int i = 0; i < 3; i++)
            {
                robotSteppers[i].setDirection(direction_increase);
            }
        }
        break;
    }
    //运行模式
    case Mode::mode_running:
        // if (stepper.curStepInOneMove != stepper.totalStepInOneMove)
        if (currentTick % 5 == 0) //脉冲上升
        {
            switch (stepper.getDir())
            {
            case direction_decrease:
                if (stepper.curStepInGlobal > 0)
                {
                    stepper.setStepPin(1);
                    stepper.curStepInGlobal--;
                }
                break;

            case direction_increase:
                stepper.setStepPin(1);
                stepper.curStepInGlobal++;
                break;
            }
        }
        else
        {
            stepper.setStepPin(0);
        }

        // if (stepper.curStepInGlobal > 0)
        // {
        //     //当前tick帧是否为脉冲上升帧
        //     if (currentTick % 5 == 0)
        //     // if (currentTick == (tickCountInOneMove - 1) * stepper.curStepInOneMove / stepper.totalStepInOneMove)
        //     {
        //         stepper.setStepPin(1);
        //         stepper.curStepInOneMove++;
        //         switch (stepper.getDir())
        //         {
        //         case Direction_Decrease:
        //             stepper.curStepInGlobal--;
        //             break;
        //         }
        //     }
        //     else
        //     {
        //     }
        // }
        break;
    }
}

/************************************
 * 
 *   一段路程切片走完后准备下一段路径
 * 
 * **********************************/
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
void RobotArmApp::calcAndSetStep(RobotStepper &stepper)
{
    switch (stepper.getId())
    {
    case 1:

        break;
    }
    //根据stepper的id来计算对应的步进值
    int step;
    stepper.setDirection((Direction)(step > 0));
    stepper.totalStepInOneMove = step > 0 ? step : -step;
}
