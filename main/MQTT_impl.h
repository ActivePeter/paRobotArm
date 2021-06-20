#ifndef __MQTT_IMPL_H__
#define __MQTT_IMPL_H__
namespace N_Mqtt
{
    void init(void);
    void sendToHost(unsigned char *data, int len);
}

#endif // __MQTT_IMPL_H__