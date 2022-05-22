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
        if(len==0){
            return;
        }
        #define match_id(b) if(data1[0]==(uint8_t)b)
        match_id(PackIds::Pos){
            // &&len>=sizeof(Pack_Pos)
            // ){
            Pack_Pos pack;
            memcpy(&pack,data1,sizeof(Pack_Pos));
            appVar.recent_cmd_pos.x=pack.x;
            appVar.recent_cmd_pos.y=pack.y;

            appVar.robotArm.pointBuff.addPoint(RobotArmPoint3D(pack.x,0,pack.y));
            lvapp::update_recent_cmd_pos();
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

    namespace send{
        SendCtx send_ctx;

        void _flush_one(){
            int packlen=0;
            int packoff=0;
            if(send_ctx.pack_cnts==1){
                packlen=send_ctx.pack_len_presum[send_ctx.pack_cnts-1];
            }
            else if(send_ctx.pack_cnts>0){
                packoff=send_ctx.pack_offsets[send_ctx.pack_cnts-2];
                packlen=send_ctx.pack_len_presum[send_ctx.pack_cnts-1]-
                    send_ctx.pack_len_presum[send_ctx.pack_cnts-2];
            }
            if(send_ctx.pack_cnts>0){
                appVar.tcp_client.client.write(send_ctx.buffer+packoff,packlen);
                // memset(send_ctx.buffer,0,sizeof(send_ctx.buffer));
                // send_ctx.pack_offsets[0]=0;
                send_ctx.pack_cnts--;
            }
        }

        void flush_all(){
            while(send_ctx.pack_cnts>0){
                _flush_one();
            }
        }

        
    }
}