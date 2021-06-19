#ifndef __TALK_H__
#define __TALK_H__
#include "paCoreInc/all"
//通信部分由于各个平台差异较大，所以不进行解耦了
namespace Talk
{
    // private:
    //     /* data */
    // public:
    paErr init();
    void msgHandle(uint8_t *data, int len);
};

#endif // __TALK_H__