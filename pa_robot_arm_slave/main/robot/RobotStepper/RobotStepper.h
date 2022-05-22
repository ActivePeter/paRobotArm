#ifndef __ROBOTSTEPPER_H__
#define __ROBOTSTEPPER_H__

#define RobotStepper_Use_A4988

class RobotStepper
{
    /**
     * 类型
     */
public:
    enum Direction
    {
        Dir_Back = 0,
        Dir_Forward,
    };

    /**
     * 驱动层
     */
public:
    void setStepPin(char state);

    void setEnPin(char state);
    char getEnPin();

    //不要直接操作方向引脚。通过setDirection来操作
    void setDirPin(char state);
#ifdef RobotStepper_Use_A4988
    static void setDividePin(bool ms1, bool ms2, bool ms3);
#endif
    // #include "_drv.inline.h"
    // private:

    /**
     * 逻辑层
     */
public:
    static void initHardware();
    RobotStepper();
    int curStepInGlobal = 0; //全局的step(几何计算结果也是全局的)，与当前全局做差即为需要步进的totalStepInOneMove，
    int curStepInOneMove = 0;
    int totalStepInOneMove = 0;

    void init(char id, bool dirInverted);
    char getId();
    Direction getDir();
    void setDirection(Direction dir);

#ifdef RobotStepper_Use_A4988
    // static void setDividePin(bool ms1, bool ms2, bool ms3);
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
    bool dirInverted = false;

private:
    void setId(char a);
    char id = 0;

    Direction direction;
};

#endif // __ROBOTSTEPPER_H__