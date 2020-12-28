#include "RobotArmApp.h"

bool RobotArmPointBuff::addPoint(RobotArmPoint3D point)
{
    if (pointCnt < RobotArmPointBuffLen)
    {
        buff[(headIndex + pointCnt) % RobotArmPointBuffLen] = point;
        pointCnt++;
    }
    // pointCnt %= RobotArmPointBuffLen;
}
bool RobotArmPointBuff::getNextPoint(RobotArmPoint3D &p)
{
    bool res = pointCnt > 0;
    if (res)
    {
        p = buff[headIndex];
        headIndex++;
        pointCnt--;
    }

    return res;
}
void RobotArmPointBuff::reset()
{
    pointCnt = 0;
    headIndex = 0;
}

bool RobotArmPointBuff::ifNeedSupply()
{
    return pointCnt < 3;
}
