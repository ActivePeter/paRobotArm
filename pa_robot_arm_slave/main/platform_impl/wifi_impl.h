#ifndef __WIFI_H__
#define __WIFI_H__

struct WifiState{
    bool connected=false;
};
namespace wifi{
    void connect();
}
#endif // __WIFI_H__