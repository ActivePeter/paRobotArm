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

    void setId(char a);
    char getId();
    void setStepPin(char state);
    void setDirPin(char state);
    void setEnPin(char state);
#ifdef RobotStepper_Use_A4988
    static void setDividePin(bool ms1, bool ms2, bool ms3);
    enum Divide_a4988
    {
        Divide_a4988_1,
        Divide_a4988_2,
        Divide_a4988_4,
        Divide_a4988_8,
        Divide_a4988_16
    };
    static void setDivide(Divide_a4988 divide);
#endif

private:
    char id = 0;
};

#endif // __ROBOTSTEPPER_H__