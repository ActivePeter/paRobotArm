#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__

namespace communication{
    enum class PackIds
    {
        Pos = 0,
        AlreadyReset = 1,//机械臂已经复位  下->上
		SwitchMotorEn = 2,//切换机械臂开关状态  上/下
    };
    namespace Packs{
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
            Pack_SwitchMotorEn(uint8_t switch_en_):switch_en(switch_en_){}
        };
    }

    void handle_data(char * data1,int len);
    // void try_send_data(char * data1,int len);
    namespace send{
        class SendCtx{
        public:
            char buffer[8192]={0};
            int pack_len_presum[100]={0};
            int pack_cnts=0;
        };
        extern SendCtx send_ctx;

        void flush_all();
        
        //将数据加入缓存
        template<typename T>
        bool send_data(PackIds packid,T &data);
    }
}
#endif // __COMMUNICATION_H__