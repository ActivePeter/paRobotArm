#include "paCoreInc/drv/paBase.h"
#include "esp_log.h"

// inline
void paBase::output(const char *data)
{
    // ESP_LOGI("paOut", data);
    esp_log_write(ESP_LOG_INFO, "paOut", "%s\r\n", data);
}
