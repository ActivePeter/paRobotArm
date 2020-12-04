#include "pa_Defines.h"
#ifndef __ROBOTSTEPPER_H__
#define __ROBOTSTEPPER_H__
#include "../../../drv/pa_CommonDrv/pa_CommonDrv.h"

#define RobotStepper_Use_A4988

class RobotStepper
{
public:
    RobotStepper();
    int curStepInGlobal = 0;
    int curStepInOneMove = 0;
    int totalStepInOneMove = 0;
    int stepInGlobal = 0; //全局的step(几何计算结果也是全局的)，与当前全局做差即为需要步进的totalStepInOneMove，
    Direction stepDirection;

    void init(char id, bool dirInverted);
    char getId();
    Direction getDir();
    void setStepPin(char state);
    void setDirection(Direction dir);
    void setEnPin(char state);
#ifdef RobotStepper_Use_A4988
    static void setDividePin(bool ms1, bool ms2, bool ms3);
    enum Divide_a4988
    {
        divide_a4988_1,
        divide_a4988_2,
        divide_a4988_4,
        divide_a4988_8,
        divide_a4988_16
    };
    static void setDivide(Divide_a4988 divide);
#endif

private:
    //不要直接操作方向引脚。通过setDirection来操作
    void setDirPin(char state);
    void setId(char a);
    char id = 0;
    bool dirInverted;
    Direction direction;
};

#endif // __ROBOTSTEPPER_H__