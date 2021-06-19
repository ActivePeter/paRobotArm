#include "MainApp.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
#include "paCoreInc/all"
#include "paMods/display/SSD1306/pa_oled.h"
// #include "paCoreHead/paIIC.h"
// #include "paCoreHead/paBase.h"
// #include "paCoreHead/paSPI.h"
// #include "paCoreHead/paBase.h"

#include "Talk.h"
#include "MainAppVar.h"
App app;
void timerCall_100us()
{
    app.robotArm.onTimerTick();
}
void mainAppEntry()
{

    // app.talk.init();
    Talk::init();
    // _G_paIIC.init(0);
    _G_paSPI.init(0);
    app.lcd.init(0, pa_ILI9341::Rotation_HORIZONTAL_1);

    // _G_paGPIO.init(N_paGPIO::Mode_Output, RobotArm_GPIO_En0);
    // _G_paGPIO.write(RobotArm_GPIO_En0, 0);
    app.robotArm.init();
    _G_paTimer.initWithCallBack(100, timerCall_100us);

    int helloCnt = 0;
    while (1)
    {

        // _G_paGPIO.write(Conf_ILI9341_CS, 1);
        // _G_paGPIO.write(Conf_ILI9341_RST, 1);
        // _G_paGPIO.write(Conf_ILI9341_DC, 1);
        // ESP_LOGI("App", "hello world!");

        helloCnt++;
        if (helloCnt % 1000 == 0)
        {
            helloCnt = 0;
            _G_paBase.output("hello world");
        }

        _G_paBase.delayMs(2);
        // vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}