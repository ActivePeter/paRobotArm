#include "paCoreInc/drv/paTimer.h"
#include "esp_timer.h"
esp_timer_create_args_t periodic_timer_args;

paErr paTimer::initWithCallBack(int us, void (*callback1)())
{
    callback = callback1;
    {
        periodic_timer_args.callback = [](void *)
        {
            if (_G_paTimer.isOn)
            {
                _G_paTimer.callback();
            }
        };
        /* name is optional, but may help identify the timer when debugging */
        periodic_timer_args.name = "periodic";
    }
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));

    // esp_timer_start_periodic(periodic_timer, 500000);
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, us));
    isOn = true;

    return E_Succ;
}
