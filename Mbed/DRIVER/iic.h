/*
 * @C++ FILES: 
 * @Descripttion: 
 * @version: 
 * @Author: TheiiKu
 * @Date: 2023-10-30 10:37:24
 * @LastEditors: TheiiKu
 * @LastEditTime: 2023-11-20 09:52:34
 * @afterAnnotation: CRATED IN JLU SENSOR LAB
 */
#ifndef _IIC_H_
#define _IIC_H_

#include "nrf.h"

#include "nrf_gpio.h"

#include "nrf_drv_twi.h"

#include "include.h"


#define TWI_INSTANCE_ID     1

/* Number of possible TWI addresses. */
#define TWI_ADDRESSES      127

#define SCL_PIN   NRF_GPIO_PIN_MAP(0,2)

#define SDA_PIN    NRF_GPIO_PIN_MAP(0,31)


extern const nrf_drv_twi_t m_twi;

extern volatile u8 I2C_FastMode;

void I2C_INIT (void);

void user_delay_ms(uint32_t period);

int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);


bool device_verify_bme280_product_id(u8 dev_id);

bool device_verify_mpu6050_product_id(u8 dev_id);


u8 IIC_Write_1Byte(u8 SlaveAddress,u8 REG_Address,u8 REG_data);

u8 IIC_Read_1Byte(u8 SlaveAddress,u8 REG_Address,u8 *REG_data);

u8 IIC_Write_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf);

u8 IIC_Read_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf);

#endif
