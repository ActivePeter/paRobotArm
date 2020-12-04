#include "RobotStepper.h"

RobotStepper::RobotStepper() {}

void RobotStepper::setId(char a)
{
    id = a;
}

char RobotStepper::getId()
{
    return id;
}

#ifdef RobotStepper_Use_A4988
void RobotStepper::setDivide(Divide_a4988 divide)
{
    switch (divide)
    {
    case Divide_a4988_1:
        RobotStepper::setDividePin(0, 0, 0);
        break;
    case Divide_a4988_2:
        RobotStepper::setDividePin(1, 0, 0);
        break;
    case Divide_a4988_4:
        RobotStepper::setDividePin(0, 1, 0);
        break;
    case Divide_a4988_8:
        RobotStepper::setDividePin(1, 1, 0);
        break;
    case Divide_a4988_16:
        RobotStepper::setDividePin(1, 1, 1);
        break;
    default:
        break;
    }
}
#endif
