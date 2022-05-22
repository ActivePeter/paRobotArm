#include "tcpclient.h"
#include "paLibSubs/paCoreInc/all"
#include "communication.h"
namespace tcpclient
{
    void recv_loop(void*_client)
    {
        // TcpClient&client=*((TcpClient*)_client);
        // while(client.client.connected()){
        //     if(client.client.available())
        //     {
        //         static char buf[1000];
        //         auto len=client.client.readBytes(buf,1000);
        //         communication::handle_data(buf,len);
        //     }
        //     _G_paBase.delayMs(10);
        // }
        // client.client.stop();
    }

    void connect(TcpClient &client)
    {
        auto ok=client.client.connect("192.168.43.8", 12398);
        if(ok){
            client.connected=true;
            // xTaskCreate(
            // recv_loop,   /* Task function. */
            // "recv_loop", /* String with name of task. */
            // 10000,     /* Stack size in bytes. */
            // (void*)&client,      /* Parameter passed as input of the task */
            // 1,         /* Priority of the task. */
            // NULL);     /* Task handle. */
        }else{
            client.connected=false;
        }
    }
}