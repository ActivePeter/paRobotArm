#include "pa_Defines.h"

#ifndef __ROBOTARMAPP_H__
#define __ROBOTARMAPP_H__
#include "../RobotStepper/RobotStepper.h"
class RobotArmModel
{
public:
    RobotArmModel();
    const float l1 = 1;   //left motor connected arm len (arm1)
    const float l2_y = 1; //right motor connectd arm len (arm2)
    const float l2_x = 1; //the xoffset of head to arm2
    float l2;             //modeled arm len, calc from l2_y & l2_x
    float theata3;        //in model angle fix, calc from 12_y & 12_x
    float theata1;        //(arm1 angle)
    float theata2;        //(arm2 angle)
    void recalcVeticalPlane(float x, float y);
    void initDatas();

private:
    float l2Square;
    float l1Square;
};
class RobotArmApp
{
public:
    RobotArmApp();
    static RobotArmApp instance;
    void onTimerTick();

    enum Mode
    {
        mode_backup,
        mode_running
    };
    void setMode(Mode mode);
    void init();

    /**************************************
     * 
     *      硬件层
     * 
     **************************************/
    char getLimitSwitch_LeftArm();
    char getLimitSwitch_RightArm();
    void setMotorEnable(char enable);

private:
    Mode curMode;
    RobotStepper robotSteppers[3];

    bool pinStateOnBackupMode = false;

    //电机1当前步进数
    int step1 = 0;
    //电机2当前步进数
    int step2 = 0;
    //电机3当前步进数
    int step3 = 0;

    //电机1目标步进数
    int targetStep1 = 0;
    //电机1目标步进数
    int targetStep2 = 0;
    //电机1目标步进数
    int targetStep3 = 0;

    int currentStep1 = 0;

    //电机1 位移所需总步进数
    int totalStep1 = 0;
    //电机2 位移所需总步进数
    int totalStep2 = 0;
    //电机3 位移所需总步进数
    int totalStep3 = 0;

    //决定了完成总的步进需要花费的tick
    int tickCountInOneMove = 0;
    //当前tick计数
    int currentTick = 0;

    void prepareNextMove();
    void doStepperEvent(RobotStepper &stepper);
    void calcAndSetStep(RobotStepper &stepper);
};

#endif // __ROBOTARMAPP_H__