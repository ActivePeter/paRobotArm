#include "communication.h"
#include "app_var.h"
#include "lvapp.h"


namespace communication
{

    struct Pack_Pos
    {
        uint8_t id;
        int32_t x;
        int32_t y;
    };
    // bool match_id(uint8_t a,PackIds id){
    //     return a==(uint8_t)id;
    // }
    void handle_data(char *data1, int len)
    {
        if (len == 0)
        {
            return;
        }
        auto data1_=(uint8_t*)data1;
#define match_id(b) if (data1[0] == (uint8_t)b)
        match_id(PackIds::Pos)
        {
            // &&len>=sizeof(Pack_Pos)
            // ){
            Pack_Pos pack;
            memcpy(&pack, data1+1, sizeof(Pack_Pos));
            appVar.recent_cmd_pos.x = pack.x;
            appVar.recent_cmd_pos.y = pack.y;

            appVar.robotArm.pointBuff.addPoint(RobotArmPoint3D(pack.x, 0, pack.y));
            lvapp::update_recent_cmd_pos();
        }
        match_id(PackIds::SwitchMotorEn){
            Packs::Pack_SwitchMotorEn pack;
            memcpy(&pack, data1+1, sizeof(Packs::Pack_SwitchMotorEn));

            lvapp::set_robot_arm_motor_en_switch(pack.switch_en);
            Serial.printf("SwitchMotorEn %d\n",pack.switch_en);
        }
        match_id(PackIds::ABunchOfPoint){
            uint32_t pcnt=0;
            memcpy(&pcnt,data1+1,4);
            if(pcnt*sizeof(Packs::Pack_SinglePoint)+5==len){
                for(int i=0;i<pcnt;i++){
                    auto pack=Packs::make_pack_from_buf<Packs::Pack_SinglePoint>(
                        data1+5+i*sizeof(Packs::Pack_SinglePoint));
                    if(i==0){
                        Serial.printf("%d head ",len);
                        for(int j=0;j<4;j++){
                            Serial.printf("%d ",*(data1_+1+j));
                        }
                        Serial.printf("\nraw ");
                        for(int j=0;j<12;j++){
                            Serial.printf("%d ",*(data1_+5+j));
                        }
                        Serial.printf("\nABunchOfPoint first p %f %f %f\n",
                            pack.x,pack.y,pack.z);
                    }
                    appVar.robotArm.pointBuff.addPoint(RobotArmPoint3D(pack.x,pack.y, pack.z));
                }
            }else{
                Serial.printf("ABunchOfPoint wrong packlen %d\n",len);
            }
            
        }
    }

    // size_t try_send_data(char *data1, int len)
    // {
    //     if(appVar.tcp_client.connected
    //     // &&
    //         ){
    //         return appVar.tcp_client.client.write(data1,len);
    //     }
    //     return 0;
    // }

    namespace send
    {

        size_t SendCtx::get_left_space()
        {
            if (pack_cnts == 0)
            {
                return sizeof(buffer);
            }
            return sizeof(buffer) - pack_len_presum[pack_cnts - 1];
        }

        SendCtx send_ctx;

        void _flush_one()
        {
            int packlen = 0;
            int packoff = 0;
            if (send_ctx.pack_cnts == 1)
            {
                packlen = send_ctx.pack_len_presum[send_ctx.pack_cnts - 1];
            }
            else if (send_ctx.pack_cnts > 0)
            {
                packoff = send_ctx.pack_len_presum[send_ctx.pack_cnts - 2];
                packlen = send_ctx.pack_len_presum[send_ctx.pack_cnts - 1] -
                          send_ctx.pack_len_presum[send_ctx.pack_cnts - 2];
            }
            if (send_ctx.pack_cnts > 0)
            {
                // Serial.printf("%d %d\n",send_ctx.buffer[packoff],send_ctx.buffer[packoff+1]);
                appVar.tcp_client.
                    //client.write
                    send_
                    ((char *)(send_ctx.buffer) + packoff, packlen);
                // memset(send_ctx.buffer,0,sizeof(send_ctx.buffer));
                // send_ctx.pack_offsets[0]=0;
                send_ctx.pack_cnts--;
            }
        }

        void flush_all()
        {
            if (send_ctx.pack_cnts > 0)
            {
                Serial.printf("left pack %d\n",send_ctx.pack_cnts);
            }

            while (send_ctx.pack_cnts > 0)
            {

                _flush_one();
            }
        }

    }
}