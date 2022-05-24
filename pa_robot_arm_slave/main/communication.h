#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__
#include "paCoreInc/all"
#include "string.h"

namespace communication
{
    enum class PackIds
    {
        Pos = 0,
        AlreadyReset = 1,  //机械臂已经复位  下->上
        SwitchMotorEn = 2, //切换机械臂开关状态  上/下
        ABunchOfPoint = 3,
    };
    namespace Packs
    {
        template <typename T>
        T make_pack_from_buf(char * buff){
            T pack;
            memcpy(&pack,buff,sizeof(T));
            return pack;
        }
        // struct Pack_Pos
        // {
        //     uint8_t id;
        //     int32_t x;
        //     int32_t y;
        // };
        // struct Pack_AlreadyReset
        // {
        //     uint8_t id;
        //     uint8_t already_reset;
        // };
        struct Pack_SwitchMotorEn
        {
            // uint8_t id;
            uint8_t switch_en;
            Pack_SwitchMotorEn() {}
            Pack_SwitchMotorEn(uint8_t switch_en_) : switch_en(switch_en_) {}
        };
        struct Pack_AlreadyReset
        {
        };
        struct Pack_SinglePoint
        {
            float x;
            float y;
            float z;
        };
        // struct Pack_TaskDisc{
        //     int32_t total_point_cnt;
        //     Pack_TaskDisc(int32_t total_point_cnt_):total_point_cnt(total_point_cnt_){}
        // };
        // //在剩余点数小于一定量时，发送一波点
        // struct Pack_FinishedPointCnt{

        //     int32_t cnt;
        //     Pack_FinishedPointCnt(int32_t cnt_):cnt(cnt_){}
        // };
    }

    void handle_data(char *data1, int len);
    // void try_send_data(char * data1,int len);
    namespace send
    {
        class SendCtx
        {
        public:
            char buffer[4096] = {0};
            int pack_len_presum[100] = {0}; // pack包的前缀和
            int pack_cnts = 0;
            size_t get_left_space();
        };
        extern SendCtx send_ctx;

        void flush_all();

        //将数据加入缓存
        template <typename T>
        bool send_data(PackIds packid, T &data);
    }
}

#include "communication.temp.h"
#endif // __COMMUNICATION_H__