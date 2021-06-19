#include "Talk.h"
#include "MQTT_impl.h"
#include "MainAppVar.h"
namespace Talk
{
    paErr init()
    {

        N_Mqtt::init();
        return E_Succ;
    }

    void msgHandle(uint8_t *data, int len)
    {
        app.robotArm.parseMsg(data, len);
    }
}