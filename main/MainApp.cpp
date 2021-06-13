#include "MainApp.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

void mainAppEntry()
{
    while (1)
    {
        ESP_LOGI("App", "hello world!");
        vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    }
}