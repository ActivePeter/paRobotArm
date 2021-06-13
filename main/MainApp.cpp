#include "MainApp.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "paMods/display/SSD1306/pa_oled.h"
#include "paCoreHead/paIIC.h"
void mainAppEntry()
{
    _G_paIIC.init();
    OLED_Init(0);
    while (1)
    {
        ESP_LOGI("App", "hello world!");
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}