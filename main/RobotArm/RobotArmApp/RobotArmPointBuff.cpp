#include "RobotArmApp.h"

bool RobotArmPointBuff::addPoint(RobotArmPoint3D point)
{
    if (pointCnt < RobotArmPointBuffLen)
    {
        buff[(headIndex + pointCnt) % RobotArmPointBuffLen] = point;
        pointCnt++;
        return true;
    }
    return false;
    // pointCnt %= RobotArmPointBuffLen;
}
bool RobotArmPointBuff::getNextPoint(RobotArmPoint3D &p)
{
    bool res = pointCnt > 0;
    if (res)
    {
        p = buff[headIndex];
        headIndex++;
        headIndex %= RobotArmPointBuffLen;
        pointCnt--;
        // if (pointCnt == 15)
        // {
        //     needSupplyFlag = true;
        // }
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
    return pointCnt < 16;
    //     // if (needSupplyFlag)
    //     // {
    //         needSupplyFlag = false;
    //         return true;
    //     }
    //     return false;
}
