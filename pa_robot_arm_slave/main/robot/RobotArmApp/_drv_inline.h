inline char getLimitSwitch_LeftArm()
{
    return _G_paGPIO.read(RobotArm_GPIO_LeftArmLimit);
}

inline char getLimitSwitch_RightArm()
{
    return _G_paGPIO.read(RobotArm_GPIO_RightArmLimit);
}
inline void initHardware()
{
    _G_paGPIO.init(N_paGPIO::Mode_InputPullUp, RobotArm_GPIO_LeftArmLimit);
    _G_paGPIO.init(N_paGPIO::Mode_InputPullUp, RobotArm_GPIO_RightArmLimit);
}