#include "RobotArmApp.h"

void RobotArmPointBuff::addPoint(RobotArmPoint3D point)
{
    buff[pointCnt] = point;
    if (pointCnt < RobotArmPointBuffLen)
    {
        pointCnt++;
    }
    // pointCnt %= RobotArmPointBuffLen;
}
