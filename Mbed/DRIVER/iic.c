#include "iic.h"

#include "nrf_delay.h"

#include "nrf_log.h"

#include "nrf_log_ctrl.h"

const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);


volatile u8 I2C_FastMode;

void I2c_Soft_delay()
{ 
	__nop();__nop();__nop();
	__nop();__nop();__nop();
	__nop();__nop();__nop();
	
	if(!I2C_FastMode)
	{
		u8 i = 15;
		while(i--);
	}
}



void I2C_INIT (void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_config = {
       .scl                = SCL_PIN,
       .sda                = SDA_PIN,
       .frequency          = NRF_DRV_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_config, NULL, NULL);
    APP_ERROR_CHECK(err_code);
    
    nrf_drv_twi_enable(&m_twi);
}


void user_delay_ms(uint32_t period)
{
    nrf_delay_ms(period);
}



int8_t user_i2c_read(u8 dev_id, u8 reg_addr, u8 *reg_data, u16 len)
{
    ret_code_t err_code = nrf_drv_twi_tx(&m_twi,dev_id,&reg_addr,1,false);
    
    APP_ERROR_CHECK(err_code);
    
    err_code = nrf_drv_twi_rx(&m_twi,dev_id,reg_data,len);
    
    APP_ERROR_CHECK(err_code);
    
    return err_code;
}

#define MAX_WRITE_LENGTH  200
int8_t user_i2c_write(u8 dev_id, u8 reg_addr, u8 *reg_data, u16 len)
{
    ret_code_t err_code;
    
    uint8_t write_data[MAX_WRITE_LENGTH];
    
    if(len>MAX_WRITE_LENGTH-1)
    {
        err_code = 1;
        return err_code;
    }
    
    write_data[0] = reg_addr;
    
    memcpy(&write_data[1],reg_data,len);
    
    err_code = nrf_drv_twi_tx(&m_twi,dev_id,write_data,len+1,false);
    
    APP_ERROR_CHECK(err_code);
    
    return err_code;
}


bool device_verify_bme280_product_id(u8 dev_id)
{
    uint8_t bme280_id_adress = 0xD0U;
    
    uint8_t bme280_id_value = 0x60U;
    
    uint8_t read_reg_data;
    
    ret_code_t err_code = user_i2c_read(dev_id,bme280_id_adress,&read_reg_data,1);
    
    APP_ERROR_CHECK(err_code);
    
    NRF_LOG_INFO("The read ID value is:0x%x\n",read_reg_data);
    NRF_LOG_FLUSH();
    
    if(read_reg_data==bme280_id_value)
    {
        NRF_LOG_INFO("The ID value is correct,I2C communicate test pass!");
        NRF_LOG_FLUSH();
        return true; 
    }
    else
    {
        NRF_LOG_INFO("I2C communicate test faiure!");
        NRF_LOG_FLUSH();
    }
    return false;
}


bool device_verify_mpu6050_product_id(u8 dev_id)
{
    uint8_t bme280_id_adress = 0x75U;
    
    uint8_t bme280_id_value = 0x68U;
    
    uint8_t read_reg_data;
    
    ret_code_t err_code = user_i2c_read(dev_id,bme280_id_adress,&read_reg_data,1);
    
    APP_ERROR_CHECK(err_code);
    
    NRF_LOG_INFO("The read ID value is:0x%x\n",read_reg_data);
    NRF_LOG_FLUSH();
    
    if(read_reg_data==bme280_id_value)
    {
        NRF_LOG_INFO("The ID value is correct,I2C communicate test pass!");
        NRF_LOG_FLUSH();
        return true; 
    }
    else
    {
        NRF_LOG_INFO("I2C communicate test faiure!");
        NRF_LOG_FLUSH();
    }
    return false;
}



u8 IIC_Write_1Byte(u8 SlaveAddress,u8 REG_Address,u8 REG_data)
{
    ret_code_t err_code = user_i2c_write(SlaveAddress, REG_Address, &REG_data, 1);
    
    return err_code;
}

u8 IIC_Read_1Byte(u8 SlaveAddress,u8 REG_Address,u8 *REG_data)
{
    ret_code_t err_code = user_i2c_read(SlaveAddress, REG_Address, REG_data, 1);
    
    return err_code;
}

u8 IIC_Write_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf)
{
    ret_code_t err_code = user_i2c_write(SlaveAddress, REG_Address, buf, len);
    
    return err_code;
}

u8 IIC_Read_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf)
{
    ret_code_t err_code = user_i2c_read(SlaveAddress, REG_Address, buf, len);
    
    return err_code;
}


