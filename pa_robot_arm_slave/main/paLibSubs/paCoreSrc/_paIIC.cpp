#include "paCoreInc/drv/paIIC.h"
#include "driver/i2c.h"
#include "string.h"
#include "esp_log.h"

#define ACK_CHECK_EN 0x1          /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0         /*!< I2C master will not check ack from slave */
#define I2C_MASTER_SCL_IO 19      /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO 18      /*!< gpio number for I2C master data  */
#define I2C_MASTER_FREQ_HZ 100000 /*!< I2C master clock frequency */
#define I2C_TX_BUF_DISABLE 0      /*!< I2C master do not need buffer */
#define I2C_RX_BUF_DISABLE 0      /*!< I2C master do not need buffer */

#define I2C_SUCC 1
#define I2C_FAIL 0

uint8_t paIIC::init(unsigned char iicId)
{
    switch (iicId)
    {
    case 0:
    {
        int i2c_master_port = I2C_NUM_0;
        i2c_config_t conf;
        {
            memset(&conf, 0, sizeof(conf));
            conf.mode = I2C_MODE_MASTER;
            conf.sda_io_num = I2C_MASTER_SDA_IO; // select GPIO specific to your project
            conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
            conf.scl_io_num = I2C_MASTER_SCL_IO; // select GPIO specific to your project
            conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
            // conf.clk_speed = I2C_MASTER_FREQ_HZ;
            conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
            // conf.master.clk_speed = I2C_MASTER_FREQ_HZ; // select frequency specific to your project
        }
        // .clk_flags = 0,
        // = {
        //     .mode = I2C_MODE_MASTER,
        //     .sda_io_num = I2C_MASTER_SDA_IO, // select GPIO specific to your project
        //     .sda_pullup_en = GPIO_PULLUP_ENABLE,
        //     .scl_io_num = I2C_MASTER_SCL_IO, // select GPIO specific to your project
        //     .scl_pullup_en = GPIO_PULLUP_ENABLE,
        //     .master.clk_speed = I2C_MASTER_FREQ_HZ, // select frequency specific to your project
        //     // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
        // };
        esp_err_t err = i2c_param_config(i2c_master_port, &conf);
        if (err != ESP_OK)
        {
            ESP_LOGE("App", "IIC Fail1");
            return I2C_FAIL;
        }
        err = i2c_driver_install(i2c_master_port,
                                 conf.mode,
                                 I2C_RX_BUF_DISABLE, I2C_TX_BUF_DISABLE, 0);
        if (err != ESP_OK)
        {
            ESP_LOGE("App", "IIC Fail2");
            return I2C_FAIL;
        }
        // if()
    }
    break;

    default:

        ESP_LOGE("App", "IIC Fail3");
        return I2C_FAIL;
    }

    ESP_LOGI("App", "IIC Succ");
    return I2C_SUCC;
}

uint8_t paIIC::writeLen(unsigned char iicId,
                        unsigned char addr,
                        unsigned char length, ByteArr data_wr[])
{
    static i2c_cmd_handle_t cmdhandle;
    switch (iicId)
    {
    case 0:
    {
        cmdhandle = i2c_cmd_link_create();
        i2c_master_start(cmdhandle);
        //addr
        i2c_master_write_byte(cmdhandle, (addr << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
        // ESP_LOGI("IIC", "addr:%x len:%d", addr, length);
        for (int i = 0; i < length; i++)
        {
            // for(int j=0;j<data_wr[i].len;)
            // ESP_LOGI("IIC", "data:%2x %2x", *(data_wr[i].arrPtr), *(data_wr[i].arrPtr + 1));
            i2c_master_write(cmdhandle, data_wr[i].arrPtr, data_wr[i].len, ACK_CHECK_EN);
        }
        //data
        // if (size > 1)
        // {
        //     i2c_master_read(cmd, data_rd, size - 1, ACK_VAL);
        // }

        // i2c_master_read_byte(cmd, data_rd + size - 1, NACK_VAL);
        i2c_master_stop(cmdhandle);
        esp_err_t ret = i2c_master_cmd_begin(iicId, cmdhandle, 100 / portTICK_RATE_MS);
        i2c_cmd_link_delete(cmdhandle);
    }
    break;

    default:
        return 0;
    }
    return 1;
}
