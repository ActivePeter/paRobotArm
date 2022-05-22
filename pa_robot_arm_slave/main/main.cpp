#include "Arduino.h"

#include "lvapp.h"
#include "app_var.h"
#include "platform_impl/tcpclient.h"
#include "platform_impl/wifi_impl.h"
#include "communication.h"
void timer_call()
{
    static int x = 0;
    x++;
    if (x == 11)
    {
        // lvgl
        lv_tick_inc(1);
        x = 0;
    }
    appVar.robotArm.onTimerTick();
    // static int i = 0;
    // static char stepon = 1;
    // i++;
    // if (i == 2)
    // {
    //     appVar.robotArm.robotSteppers[1].setStepPin(stepon);
    //     stepon = !stepon;
    //     i = 0;
    // }
}
void cpp_main()
{
    //板载资源
    _G_paSPI.init(0);
    _G_paBase.delayMs(10);
    wifi::connect();
    tcpclient::connect(appVar.tcp_client);
    // tcpclient::connect_server();
    //外设
    appVar.lcd.init(0, pa_ILI9341::Rotation_HORIZONTAL_1);
    appVar.xpt2046.init(240, 320, 3800, 250, 3800, 330, 10);
    //机械臂
    appVar.robotArm.init();
    appVar.robotArm.setMotorEnable(0);

    // // _G_paGPIO.init(N_paGPIO::Mode_Output, RobotArm_GPIO_En0);
    // // _G_paGPIO.write(RobotArm_GPIO_En0, 0);
    _G_paTimer.initWithCallBack(100, timer_call);
    // tft.setAddrWindow(0,
    //                   0,
    //                   50,
    //                   50);
    // tft.startWrite();
    // for (int i = 0; i < 2500; i++)
    // {
    //     tft.writePixel(i / 50, i % 50, 0xff00);
    // }
    // tft.endWrite();
    // delay(1000);

    #define MAP_GET_END() 0, MAP_END
#define MAP_NEXT0(item, next, ...) next MAP_OUT
#define MAP_NEXT1(item, next) MAP_NEXT0 (item, next, 0)
#define MAP_NEXT(item, next)  MAP_NEXT1 (MAP_GET_END item, next)

    lv_init();
    lv_app_init();
    // lv_example_anim_2();
    lvapp::init_all_gui();
    while (1)
    {
        //     // Serial.write("hello\r\n");
        delay(1);
        {
            auto&client=appVar.tcp_client.client;
            if (client.connected())
            {
                if (client.available())
                {
                    static char buf[1000];
                    int wi=0;
                    while(client.available()){
                        buf[wi]=client.read();
                        wi++;
                    }
                    auto len = wi;
                    communication::handle_data(buf, len);
                }
                // _G_paBase.delayMs(10);
            }
        }
        lvapp::tick_update();
        // appVar.robotArm.onTimerTick();
    }
}

extern "C" void app_main()
{
    initArduino();
    pinMode(4, OUTPUT);
    digitalWrite(4, HIGH);
    // Do your own thing
    cpp_main();
}
