// #include "core_feature_base.h"
#include "hbird_sdk_soc.h"
#include "iic.h"




void iic_delay_1_16_us(uint32_t cnt)
{
    uint32_t i = 0;

    // when SystemCoreClock is 16Mhz, 1/16 us
    for(i=0; i<cnt; i++)
    {
        __NOP();
    }

}

void iic_Init(void)
{
    gpio_enable_output(IIC_SCL_GPIO, IOF_I2C_MASK);

    gpio_iof_config(IIC_SCL_GPIO, IOF_I2C_MASK);
    
    i2c_setup(IIC_CHANNEL, 0x1F, I2C_CTR_EN);

    

    // gpio_enable_output(IIC_SCL_GPIO, (1<<IIC_SCL_PIN));
    // gpio_enable_output(IIC_SDA_GPIO, (1<<IIC_SDA_PIN));

    // gpio_write(IIC_SCL_GPIO, (1<<IIC_SCL_PIN), 1);
    // iic_delay_1_16_us(1000000);
    // gpio_write(IIC_SCL_GPIO, (1<<IIC_SCL_PIN), 0);
    // iic_delay_1_16_us(1000000);

}