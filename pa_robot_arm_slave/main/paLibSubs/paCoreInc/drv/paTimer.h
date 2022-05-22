#ifndef __PATIMER_H__
#define __PATIMER_H__
#include "../base/_all.h"
class paTimer
{
private:
    /* data */

    //存储回调指针
    void (*callback)();

public:
    /**
     * 初始化定时器并传入回调，
     * 当然像stm32这种用cube配置的项目不需要初始化
     * 可以把us参数忽略掉
     *
     * 总之满足这个接口就行
     */
    paErr initWithCallBack(int us, void (*callback)());

    //启动
    bool isOn = false;
};
extern paTimer _G_paTimer;
#endif // __PATIMER_H__