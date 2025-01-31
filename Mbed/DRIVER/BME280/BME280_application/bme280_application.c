#include "bme280_application.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#include "ssd1306.h"

/*
In file in bme280_defs.h
In case of the macro "BME280_FLOAT_ENABLE" enabled, The outputs are in double and the units are

- Celsius for temperature
- % relative humidity
- Pascal for pressure
In case if "BME280_FLOAT_ENABLE" is not enabled, then it is

- int32_t for temperature with the units 100 * Celsius
- uint32_t for humidity with the units 1024 * % relative humidity
- uint32_t for pressure
     If macro "BME280_64BIT_ENABLE" is enabled, which it is by default, the unit is 100 * Pascal
     If this macro is disabled, Then the unit is in Pascal
*/
void print_sensor_data(struct bme280_data *comp_data)
{
#ifdef BME280_FLOAT_ENABLE

    char str[128];
    
    sprintf(str,"T:%0.2f*C ",comp_data->temperature);
    
    OLED_ShowString(0,15,(uint8_t*)str,16);
    
    sprintf(str,"P:%0.2fhPa",comp_data->pressure/100);
    
    OLED_ShowString(0,30,(uint8_t*)str,16);
    
    sprintf(str,"H:%0.2f%%", comp_data->humidity);
    
    OLED_ShowString(0,45,(uint8_t*)str,16);
    
    OLED_Refresh_Gram();

    //NRF_LOG_INFO("Print the bme280 data to oled screen now...\r\n");    
    //NRF_LOG_FLUSH();
    
    //It is not supported to print to serial com now
	//NRF_LOG_INFO("temperature:%0.2f*C   pressure:%0.2fhPa   humidity:%0.2f%%\r\n",comp_data->temperature, comp_data->pressure/100, comp_data->humidity);
    //NRF_LOG_FLUSH();
#else
    
    char str[128];
    
    sprintf(str,"T:%ld*C",comp_data->temperature/100);
    
    OLED_ShowString(0,15,(uint8_t*)str,16);
    
    sprintf(str,"P:%ldhPa",comp_data->pressure/1000);
    
    OLED_ShowString(0,30,(uint8_t*)str,16);
    
    sprintf(str,"H:%ld%%", comp_data->humidity/1000);
    
    OLED_ShowString(0,45,(uint8_t*)str,16);
    
    OLED_Refresh_Gram();
    
    //NRF_LOG_INFO("Print the bme280 data to oled screen now...\r\n");    
    //NRF_LOG_FLUSH();
    
    //It is not supported to print to serial com now
	//NRF_LOG_INFO("temperature:%ld*C   pressure:%ldhPa   humidity:%ld%%\r\n",comp_data->temperature/100, comp_data->pressure/1000, comp_data->humidity/1000);
    //NRF_LOG_FLUSH();
#endif
}




int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev)
{
	//int8_t rslt;
	uint8_t settings_sel;
	struct bme280_data comp_data;

	/* Recommended mode of operation: Indoor navigation */
	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	//rslt = bme280_set_sensor_settings(settings_sel, dev);
	bme280_set_sensor_settings(settings_sel, dev);
	//rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);
	bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

	NRF_LOG_INFO("Printing the bme280 data to oled screen now...\r\n");
    NRF_LOG_FLUSH();
	while (1) {
		/* Delay while the sensor completes a measurement */
		dev->delay_ms(70);
		//rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
		bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
		print_sensor_data(&comp_data);
	}
	//return rslt;
}


int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev)
{
    //int8_t rslt;
    uint8_t settings_sel;
    struct bme280_data comp_data;

    /* Recommended mode of operation: Indoor navigation */
    dev->settings.osr_h = BME280_OVERSAMPLING_1X;
    dev->settings.osr_p = BME280_OVERSAMPLING_16X;
    dev->settings.osr_t = BME280_OVERSAMPLING_2X;
    dev->settings.filter = BME280_FILTER_COEFF_16;

    settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

    //rslt = bme280_set_sensor_settings(settings_sel, dev);
	bme280_set_sensor_settings(settings_sel, dev);

    NRF_LOG_INFO("Printing the bme280 data to oled screen now...\r\n");
    NRF_LOG_FLUSH();
    /* Continuously stream sensor data */
    while (1) {
        //rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, dev);
		bme280_set_sensor_mode(BME280_FORCED_MODE, dev);
        /* Wait for the measurement to complete and print data @25Hz */
        dev->delay_ms(40);
        //rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
		bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
        print_sensor_data(&comp_data);
    }
    //return rslt;
}
