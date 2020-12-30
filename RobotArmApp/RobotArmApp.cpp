#include "RobotArmApp.h"
#include "RobotArm_UserInterface.h"
#include "pa_CommonLib/src/drv/pa_PWM/pa_PWM.h"
#include "pa_CommonLib/src/util/pa_Math/pa_Math.h"

RobotArmApp RobotArmApp::instance = RobotArmApp();
RobotArmApp::RobotArmApp() {}

void RobotArmApp::onTimerTick()
{
    static bool pinStateOnBackupMode = false;
    if (sleepTickCnt > 0)
    {
        sleepTickCnt--;
        return;
    }
    switch (curMode)
    {
    case Mode::mode_backup:
    {
        static char backUpCnt = 0;
        pinStateOnBackupMode = backUpCnt > 0;
        backUpCnt++;
        backUpCnt %= 5;
    }
        // pinStateOnBackupMode = !pinStateOnBackupMode;
        for (int i = 0; i < 2; i++)
        {
            doStepperEvent(robotSteppers[i], pinStateOnBackupMode);
        }
        break;
    case Mode::mode_running:
        if (currentTick < tickCountInOneMove)
        {
            for (int i = 0; i < 3; i++)
            {
                doStepperEvent(robotSteppers[i], false);
            }
            currentTick++;
        }
        else
        {
            prepareNextMove(false);
        }
        // if (currentTick == tickCountInOneMove)
        // {
        //     prepareNextMove();
        // }
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
    robotSteppers[1].init(1, RobotArmStepper2_Inverted);
    robotSteppers[2].init(2, RobotArmStepper3_Inverted);
#ifdef RobotStepper_Use_A4988
    RobotStepper::setDivide(RobotStepper::divide_a4988_8);
#endif
    robotArmModel.initDatas();
}

void RobotArmApp::setMotorEnable(char enable)
{
    if (!enable)
    {
        this->curMode = Mode::mode_backup;
        pointBuff.reset();
        robotSteppers[0].init(0, RobotArmStepper1_Inverted);
        robotSteppers[1].init(1, RobotArmStepper2_Inverted);
        robotSteppers[2].init(2, RobotArmStepper3_Inverted);
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
void RobotArmApp::doStepperEvent(RobotStepper &stepper, bool pinStateOnBackupMode)
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
                limitSwitchActivatedCnt_RightArm = 0;
                // pinStateOnBackupMode = !pinStateOnBackupMode;
            }
            else if (limitSwitchActivatedCnt_RightArm < limitSwitchActivatedCnt_MAX)
            {
                limitSwitchActivatedCnt_RightArm++;
            }
            break;
        default:
            break;
        }
        //全部已经复位的条件满足后
        if (limitSwitchActivatedCnt_LeftArm == limitSwitchActivatedCnt_MAX && limitSwitchActivatedCnt_RightArm == limitSwitchActivatedCnt_MAX)
        {
            curMode = Mode::mode_running;
            sleepTickCnt = 30000;
            prepareNextMove(true);
            // for (int i = 0; i < 3; i++)
            // {
            //     robotSteppers[i].setDirection(direction_increase);
            // }
        }
        break;
    }
    //运行模式
    case Mode::mode_running:
        // if (stepper.curStepInOneMove != stepper.totalStepInOneMove)
        // if (currentTick % 5 == 0)
        if (stepper.totalStepInOneMove == 0)
        {
            stepper.setStepPin(0);
        }
        else if (currentTick == (tickCountInOneMove)*stepper.curStepInOneMove / stepper.totalStepInOneMove) //脉冲上升
        {
            switch (stepper.getDir())
            {
            case direction_decrease:
                if (stepper.getId() == 2)
                {
                    stepper.setStepPin(1);
                    stepper.curStepInGlobal--;
                    stepper.curStepInOneMove++;
                }
                else if (stepper.curStepInGlobal > 0)
                {
                    stepper.setStepPin(1);
                    stepper.curStepInGlobal--;
                    stepper.curStepInOneMove++;
                }
                break;

            case direction_increase:
                stepper.setStepPin(1);
                stepper.curStepInGlobal++;
                stepper.curStepInOneMove++;
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
void RobotArmApp::prepareNextMove(bool firstRun)
{
    static RobotArmPoint3D lastPoint;
    RobotArmPoint3D targetPoint;
    bool hasPoint = pointBuff.getNextPoint(targetPoint);
    if (hasPoint)
    {
        //tick计数清0
        currentTick = 0;
        //先赋值下一次步进完成所需要的时间 tickCountInOneMove
        if (firstRun)
        {
            this->tickCountInOneMove = 50000; // / 5;
        }
        else
        {
            float dx = targetPoint.x - lastPoint.x;
            float dy = targetPoint.y - lastPoint.y;
            float dz = targetPoint.z - lastPoint.z;
            int distance = sqrtf(dx * dx + dy * dy + dz * dz);
            this->tickCountInOneMove = (distance + 1) * 300; // / 5;
            // if(tickCountInOneMove)
        }

        int step1, step2, step3;

        // static char curStarPoint = 0;
        // static char lineStep = 0;
        // float angle = (int)curStarPoint * 4 / 5.0 * PI;
        // float angle2 = (int)(curStarPoint + 1) * 4 / 5.0 * PI;
        // float r = 25;
        // float x1 = 200 + r * cosf(angle);
        // float y1 = 0 + r * sinf(angle);
        // float x2 = 200 + r * cosf(angle2);
        // float y2 = 0 + r * sinf(angle2);

        robotArmModel.recalcVeticalPlane(targetPoint.x, targetPoint.y, targetPoint.z, step1, step2, step3);

        for (int i = 0; i < 3; i++)
        {
            //步进值计数复位  stepper.curStepInOneMove;
            robotSteppers[i].curStepInOneMove = 0;
            //然后计算三个步进所需要的步进数 stepper.totalStepInOneMove
            setStep(robotSteppers[i], step1, step2, step3);
        }
        // lineStep++;
        // if (lineStep == 5)
        // {
        //     lineStep = 0;
        //     curStarPoint++;
        //     curStarPoint %= 5;
        // }
        lastPoint = targetPoint;
    }

    //设置三个步进的步进方向
}

void RobotArmApp::setStep(RobotStepper &stepper, int m1step, int m2step, int m3step)
{
    int step;
    switch (stepper.getId())
    {
    case 0:
        // step = RobotArmStepCnt_LeftArmVertical_divide8 - RobotArmStepCnt_PI_4_divide8;
        step = m1step;
        break;
    case 1:
        // step = RobotArmStepCnt_RightArmVertical_divide8 + RobotArmStepCnt_PI_4_divide8;
        step = m2step;
        break;
    case 2:
        step = m3step;
    }

    step = step - stepper.curStepInGlobal;
    stepper.setDirection((Direction)(step > 0));
    stepper.totalStepInOneMove = step > 0 ? step : -step;
}
