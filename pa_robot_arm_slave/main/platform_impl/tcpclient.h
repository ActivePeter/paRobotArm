#ifndef __TCPCLIENT_H__
#define __TCPCLIENT_H__
#include "Wifi.h"
struct TcpClient{
    WiFiClient client;
    bool connected=false;
    int sock=-1;
    int recv_(char * data,int len);
    int send_(char * data,int len);
    void close_();
};
namespace tcpclient{
    void recv_loop();
    bool connect(TcpClient &client);
}
#endif // __TCPCLIENT_H__