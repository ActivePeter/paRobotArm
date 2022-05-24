#include "communication.h"
#include "string.h"
#include "Arduino.h"

namespace communication{
    // void try_send_data(char * data1,int len);
    namespace send{
        template<typename T>
        bool send_data(PackIds packid,T &data){
            //数量到达上限
            if(send_ctx.pack_cnts==100){
                return false;
            }
            size_t left_size=send_ctx.get_left_space();
            size_t cur_pack_offset=0;
            //剩余空间不足
            if(left_size<sizeof(T)+1){
                return false;
            }
            
            if(send_ctx.pack_cnts==0){
                send_ctx.pack_len_presum[send_ctx.pack_cnts]=1+sizeof(T);
            }else{
                send_ctx.pack_len_presum[send_ctx.pack_cnts]=
                    send_ctx.pack_len_presum[send_ctx.pack_cnts-1]+1+sizeof(T);
                cur_pack_offset=send_ctx.pack_len_presum[send_ctx.pack_cnts-1];
            }
            send_ctx.pack_cnts++;
            
            send_ctx.buffer[cur_pack_offset]=(uint8_t)packid;
            memcpy(send_ctx.buffer+1,&data,sizeof(T));
            
            // memset(send_ctx.buffer+cur_pack_offset+1,0,sizeof(T));
            return true;
            // if(appVar.tcp_client.connected
            // &&
                // ){
            //    appVar.tcp_client.client.write((char*)&data,sizeof(data));
            // }
        }
    }
}
