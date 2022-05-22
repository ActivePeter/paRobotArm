#include "wifi_impl.h"
#include "Arduino.h"
#include "WiFi.h"
#include "app_var.h"
const char* ssid ="Redmi_4810";
const char*password =  "1234567890";

namespace wifi
{
    void connect()
    {
        Serial.begin(115200);

        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.println("Establishingconnection to WiFi..");
        }
        Serial.println("Connectedto network");
        appVar.wifi_state.connected=true;
    }
}