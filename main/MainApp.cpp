#include "MainApp.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "paMods/display/SSD1306/pa_oled.h"
#include "paCoreHead/paIIC.h"
#include "paCoreHead/paBase.h"

void mainAppEntry()
{

    _G_paIIC.init(0);
    OLED_Init(0);
    // OLED_On();
    OLED_ShowString(0, 0, "121", 12);
    while (1)
    {
        // ESP_LOGI("App", "hello world!");
        _G_paBase.output("hello world");
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}