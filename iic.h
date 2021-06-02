
#ifndef __IIC_H__
#define __IIC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hbird_sdk_soc.h"


// // soft iic 
// #define IIC_SCL_GPIO GPIOB 
// #define IIC_SDA_GPIO GPIOB
// #define IIC_SCL_PIN  30  # FPGA AA21
// #define IIC_SDA_PIN  28  # FPGA AA20


#define IIC_CHANNEL I2C1

#define IIC_SCL_GPIO GPIOB 
#define IIC_SDA_GPIO GPIOB
#define IIC_SCL_PIN  14  // FPGA P14
#define IIC_SDA_PIN  15  // FPGA V17


// hardware iic0 is connected to EEPROM
/*
#define IIC_CHANNEL IIC0

#define IIC_SCL_GPIO GPIOA 
#define IIC_SDA_GPIO GPIOA
#define IIC_SCL_PIN  14  # FPGA AA9
#define IIC_SDA_PIN  15  # FPGA N14
*/

extern void iic_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __IIC_H_  */