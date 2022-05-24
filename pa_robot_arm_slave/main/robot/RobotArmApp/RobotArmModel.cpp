#include "RobotArmApp.h"
#include "robot_math.h"

// #include "pa_CommonLib/src/util/pa_Math/pa_Math.h"
RobotArmModel::RobotArmModel()
{
}

//detailed model
// please check model_describe.md
// & https://hanbaoaaa.xyz/tuchuang/images/2022/04/22/image-20220422211826234.png
void RobotArmModel::recalcVeticalPlane(float x, float y, float z, int &m1Step, int &m2Step, int &m3Step)
{
    const float headlen=55;
    const float center_to_mainarm_root=42.5f;
    const float bottom_r=76.5f;
    x+=bottom_r;

    //theata1 主臂角度
    //theata2 副臂角度
    float l3_on_xz=sqrt(x*x+z*z)-headlen-center_to_mainarm_root;

    //垂直面极坐标
    //tan=y/x;
    float pi_minust1_minust4 = atan2f(y,l3_on_xz);

    // if (theata4plus1 < 0)
    // {
    //     theata4plus1 += PI + PI;
    // }

    //之前这里没有加z。所以是有bug的
    float l3Square = l3_on_xz*l3_on_xz+y*y;
    float l3 = sqrtf(l3Square);

    float theata3plus2 = acosf((l2Square + l1Square - l3Square) / (2 * l1 * l2));
    float theata4 = acosf((l1Square + l3Square - l2Square) / (2 * l1 * l3));
    theata2 = theata3plus2 - theata3;
    theata1 = PI - pi_minust1_minust4 - theata4; 
    //theata3plus2+theata4+pi_minust1_minust5;//PI-(PI-theata3plus2-theata4-pi_minust1_minust5);

    // theata1=PI_4*3;
    // theata2=PI_4*2- theata3;

    //xz极坐标
    float theataXZ = atan2f(z, x);
    m3Step = theataXZ * RobotArmStepCnt_PI_4_divide8 / PI_4 ;

    //对应threata1
    m2Step = theata1 * RobotArmStepCnt_PI_4_divide8 / PI_4;
    //垂直-90，到0度 再+theata1
    m2Step = m2Step - 2 * RobotArmStepCnt_PI_4_divide8 + RobotArmStepCnt_RightArmVertical_divide8;

    m1Step = (theata1 - theata2) * RobotArmStepCnt_PI_4_divide8 / PI_4;
    m1Step = RobotArmStepCnt_LeftArmVertical_divide8 + m1Step - 2 * RobotArmStepCnt_PI_4_divide8;
}

void RobotArmModel::initDatas()
{
    l2Square = l2_y * l2_y + l2_x + l2_x;
    l2 = sqrtf(l2Square);
    l1Square = l1 * l1;
    theata3 = atan2f(l2_x, l2_y);
}
