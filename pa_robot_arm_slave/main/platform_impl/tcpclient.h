#ifndef __TCPCLIENT_H__
#define __TCPCLIENT_H__
#include "Wifi.h"
struct TcpClient{
    WiFiClient client;
    bool connected=false;
};
namespace tcpclient{
    void recv_loop();
    void connect(TcpClient &client);
}
#endif // __TCPCLIENT_H__