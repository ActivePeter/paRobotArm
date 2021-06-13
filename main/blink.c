/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
// #include "led_strip.h"
#include "sdkconfig.h"
#include "MainApp.h"

void app_main(void)
{
    mainAppEntry();
    /* Configure the peripheral according to the LED type */
    // configure_led();

    // while (1)
    // {
    //     ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
    //     blink_led();
    //     /* Toggle the LED state */
    //     s_led_state = !s_led_state;
    //     vTaskDelay(CONFIG_BLINK_PERIOD / portTICK_PERIOD_MS);
    // }
}
