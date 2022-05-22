#include "paCoreInc/drv/paSPI.h"
#include "driver/spi_master.h"
#include "_paSPI.PLATFORM.h"
#include "esp_system.h"
#include "string.h"
#include "esp_log.h"

#include "Arduino.h"
#include "SPI.h"

// spi_device_handle_t spi_handle;
namespace N_paSPI
{
    spi_device_handle_t spi_handle;
    void callback(spi_transaction_t *trans)
    {
    }
}
using namespace N_paSPI;

paErr paSPI::init(char spiId)
{

    SPI.setFrequency(40 * 1000 * 1000);
    SPI.begin();
        spi_bus_config_t buscfg;
        {
            memset(&buscfg, 0, sizeof(spi_bus_config_t));
            buscfg.miso_io_num = PIN_NUM_MISO;
            buscfg.mosi_io_num = PIN_NUM_MOSI;
            buscfg.sclk_io_num = PIN_NUM_CLK;
            buscfg.quadwp_io_num = -1;
            buscfg.quadhd_io_num = -1;
            buscfg.max_transfer_sz = SOC_SPI_MAXIMUM_BUFFER_SIZE;
        }

        spi_device_interface_config_t devcfg;
        {
            memset(&devcfg, 0, sizeof(spi_device_interface_config_t));
    #ifdef CONFIG_SPI_OVERCLOCK
            devcfg.clock_speed_hz = 26 * 1000 * 1000; //Clock out at 26 MHz
    #else
            devcfg.clock_speed_hz = SPI_MASTER_FREQ_80M; // * 1000 * 1000; //Clock out at 10 MHz
    #endif
            devcfg.mode = 0;          //SPI mode 0
            devcfg.spics_io_num = -1; //CS pin
            devcfg.queue_size = 7;    //We want to be able to queue 7 transactions at a time
            devcfg.pre_cb = callback; //Specify pre-transfer callback to handle D/C line
            // devcfg.command_bits = 8; 这句千万不要加，加了就死活不通
        };

        esp_err_t ret;

        ret = spi_bus_initialize(PASPI_HOST, &buscfg, SPI_DMA_CH_AUTO);
        ESP_ERROR_CHECK(ret);
        if (ret != ESP_OK)
        {
            ESP_LOGE("App", "spi Fail");
            // return E_Err;
        }
        else
        {
            ESP_LOGI("App", "spi succ");
            // return E_Succ;
        }
        ret = spi_bus_add_device(PASPI_HOST, &devcfg, &spi_handle);
        ESP_ERROR_CHECK(ret);

    //     if (ret != ESP_OK)
    //     {
    //         ESP_LOGE("App", "spi Fail");
    //         return E_Err;
    //     }
    //     else
    //     {
    //         ESP_LOGI("App", "spi succ");
    return E_Succ;
    //     }
}

paErr paSPI::transmit(char spiId, unsigned char *data, unsigned int len)
{
    // SPI.beginTransaction();
    // while (len>0)
    // {
    SPI.transferBytes(data, nullptr, len);
    // len--;
    // data++;
    // }
    // SPI.endTransaction();
    // spi_transaction_t t;
    // memset(&t, 0, sizeof(t));
    // t.rxlength = 0;
    // t.rx_buffer = NULL;
    // t.tx_buffer = data;

    // int sizePer = 64;
    // while (len > 0)
    // {
    //     if (len > sizePer)
    //     {
    //         t.length = (sizePer)*8;
    //     }
    //     else
    //     {
    //         t.length = len * 8;
    //     }
    //     t.rxlength = 0;
    //     t.rx_buffer = NULL;
    //     // t.tx_data = data;
    //     // t.flags=SPI_TRANS_USE_TXDATA;

    //     /* code */
    //     // spi_device_get_trans_result()
    //     spi_device_polling_transmit(spi_handle, &t);
    //     len -= t.length / 8;
    //     t.tx_buffer += t.length / 8;
    // }

    {
        // ESP_LOGI("App", "spi send succ");
        return E_Succ;
    }
}
