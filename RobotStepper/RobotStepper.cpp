#include "RobotStepper.h"

RobotStepper::RobotStepper() {}

void RobotStepper::init(char id1, bool dirInverted1)
{
    id = id1;
    dirInverted = dirInverted1;
    setEnPin(0);
    setDirection(direction_decrease);
    setStepPin(0);
    curStepInGlobal = 0;
    curStepInOneMove = 0;
    totalStepInOneMove = 0;
}

void RobotStepper::setId(char a)
{
    id = a;
}

char RobotStepper::getId()
{
    return id;
}

Direction RobotStepper::getDir()
{
    return direction;
}

void RobotStepper::setDirection(Direction dir)
{
    direction = dir;
    if (dirInverted)
    {
        setDirPin(!dir);
    }
    else
    {
        setDirPin((char)dir);
    }
}

#ifdef RobotStepper_Use_A4988
void RobotStepper::setDivide(Divide_a4988 divide)
{
    switch (divide)
    {
    case divide_a4988_1:
        RobotStepper::setDividePin(0, 0, 0);
        break;
    case divide_a4988_2:
        RobotStepper::setDividePin(1, 0, 0);
        break;
    case divide_a4988_4:
        RobotStepper::setDividePin(0, 1, 0);
        break;
    case divide_a4988_8:
        RobotStepper::setDividePin(1, 1, 0);
        break;
    case divide_a4988_16:
        RobotStepper::setDividePin(1, 1, 1);
        break;
    default:
        break;
    }
}
#endif
