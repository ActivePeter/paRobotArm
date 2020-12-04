#include "RobotArmApp.h"
#include "pa_CommonLib/src/util/pa_Math/pa_Math.h"
RobotArmModel::RobotArmModel()
{
}

//detailed model please check model_describe.md
void RobotArmModel::recalcVeticalPlane(float x, float y)
{
    float theata4plus1 = atan2f(y, x);

    float l3Square = x * x + y * y;
    float l3 = sqrtf(l3Square);
    float theata3plus2 = acosf((l2Square + l1Square - l3Square) / (2 * l1 * l2));
    float theata4 = acosf(l1Square + l3Square - l2Square / (2 * l1 * l3));
    theata2 = theata3plus2 - theata3;
    theata1 = theata4plus1 - theata4;
}

void RobotArmModel::initDatas()
{
    l2Square = l2_y * l2_y + l2_x + l2_x;
    l2 = sqrtf(l2Square);
    l1Square = l1 * l1;
    theata3 = atan2f(l2_x, l2_y);
}
