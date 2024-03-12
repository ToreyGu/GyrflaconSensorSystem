/*
 * @C++ FILES: 
 * 
 * @Descripttion: ADC DRIVER FOR NRF52840 DEFAULT WORK IN TWO_BUFFER MODE 
 * 					+	ALL CHANNEL ENABLE
 * 					+	TWO BUFFER WORKING MODE
 * 					DEFAULT ENABEL ALL CHANNEL ,IF PIN MEED TO WORK AS STANDARD I/O INTERFACE 
 * 					SHOULD CHANGE "SAMPLES_IN_BUFFER" AND "SignalAdcInit()" IN COSTEM
 * 
 * @version: 
 * @Author: TheiiKu
 * @Date: 2023-10-30 10:40:34
 * @LastEditors: TheiiKu
 * @LastEditTime: 2023-12-28 14:00:14
 * @afterAnnotation: CRATED IN JLU SENSOR LAB
 */



#include "BoardADC.h"


#include "nrf_drv_saadc.h"

#define SAMPLES_IN_BUFFER 8
volatile uint8_t state = 1;

float value_buffer[SAMPLES_IN_BUFFER];

static nrf_saadc_value_t     m_buffer_pool[SAMPLES_IN_BUFFER];
static uint32_t              m_adc_evt_counter;


static void adcCallbackFunc(nrf_drv_saadc_evt_t const *pEvent);

static nrf_saadc_value_t s_bufferPool[SAMPLES_IN_BUFFER];


//SAADC event callback function, in blocking mode,nothing to do in function.
void saadc_callback(nrf_drv_saadc_evt_t const * p_event)
{
//   nrf_saadc_value_t ADCValue;
//	 if (p_event->type == NRF_DRV_SAADC_EVT_DONE){
//		ret_code_t err_code;
//		err_code = nrf_drv_saadc_buffer_convert(p_event->data.done.p_buffer, SAMPLES_IN_BUFFER);
//    APP_ERROR_CHECK(err_code);
//		for (int i = 0; i < SAMPLES_IN_BUFFER; i++){
//           	ADCValue = p_event->data.done.p_buffer[i];	
//            value_buffer[i] = ADCValue;
//        	}
//		}
}
void saadc_calibrarte(void){


}

void SignalAdcInit(void){
//			ret_code_t err_code;
//			
//				
//			//register callback function 
//			err_code=nrf_drv_saadc_init(NULL,saadc_callback);
//			//chonfig struct for saadc channel?
//			nrf_saadc_channel_config_t config_0 = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN0); 
//			err_code = nrf_drv_saadc_channel_init(0, &config_0);
//			APP_ERROR_CHECK(err_code);

//			nrf_saadc_channel_config_t config_1 = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN1); 
//			err_code = nrf_drv_saadc_channel_init(1, &config_1);
//			APP_ERROR_CHECK(err_code);
//	
//			nrf_saadc_channel_config_t config_2 = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN2); 
//			err_code = nrf_drv_saadc_channel_init(2, &config_2);
//			APP_ERROR_CHECK(err_code);

//			nrf_saadc_channel_config_t config_3 = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN3); 
//			err_code = nrf_drv_saadc_channel_init(3, &config_3);
//			APP_ERROR_CHECK(err_code);
//			
//			nrf_saadc_channel_config_t config_4 = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN4);
//			err_code = nrf_drv_saadc_channel_init(4, &config_4);
//			APP_ERROR_CHECK(err_code);
//			
//			nrf_saadc_channel_config_t config_5 = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN5);
//			err_code = nrf_drv_saadc_channel_init(5, &config_5);
//			APP_ERROR_CHECK(err_code);
//			
//			nrf_saadc_channel_config_t config_6 = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN6);
//			err_code = nrf_drv_saadc_channel_init(6, &config_6);
//			APP_ERROR_CHECK(err_code);
//			
//			nrf_saadc_channel_config_t config_7 = NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN7);
//			err_code = nrf_drv_saadc_channel_init(7, &config_7);
//			APP_ERROR_CHECK(err_code);

//			
//			err_code=nrf_drv_saadc_buffer_convert(m_buffer_pool,SAMPLES_IN_BUFFER);
//			APP_ERROR_CHECK(err_code);
//    ret_code_t err_code;
//		nrf_drv_saadc_config_t saadc_config = NRF_DRV_SAADC_DEFAULT_CONFIG;
//    nrf_saadc_channel_config_t channel_config_0 =
//        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN0);
//		nrf_saadc_channel_config_t channel_config_1 =
//        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN1);
//    err_code = nrf_drv_saadc_init(&saadc_config, saadc_callback);
//    APP_ERROR_CHECK(err_code);

//    err_code = nrf_drv_saadc_channel_init(0, &channel_config_0);
//		err_code = nrf_drv_saadc_channel_init(1, &channel_config_1);
//    APP_ERROR_CHECK(err_code);

//    err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool, SAMPLES_IN_BUFFER);
//    APP_ERROR_CHECK(err_code);

//saadc pin AIN7 AND AIN0 WAS OCCUPIED BY I2C BUS 
//IN THIS PROJECT ONLY DEFINE PINS WE NEED 
		ret_code_t err_code;
		
		APP_ERROR_CHECK(err_code);

    nrf_saadc_channel_config_t channel_config_0 =
		NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_DIFFERENTIAL(NRF_SAADC_INPUT_AIN1,NRF_SAADC_INPUT_AIN3);

		nrf_saadc_channel_config_t channel_config_1 =
        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_DIFFERENTIAL(NRF_SAADC_INPUT_AIN5,NRF_SAADC_INPUT_AIN3);
		
		nrf_saadc_channel_config_t channel_config_2 =
        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_DIFFERENTIAL(NRF_SAADC_INPUT_AIN4,NRF_SAADC_INPUT_AIN3);
				
		nrf_saadc_channel_config_t channel_config_3 =
        NRF_DRV_SAADC_DEFAULT_CHANNEL_CONFIG_DIFFERENTIAL(NRF_SAADC_INPUT_AIN6,NRF_SAADC_INPUT_AIN3);			
		
		nrf_drv_saadc_config_t saadc_config = NRF_DRV_SAADC_DEFAULT_CONFIG;
		saadc_config.resolution = NRF_SAADC_RESOLUTION_12BIT;
    err_code = nrf_drv_saadc_init(NULL, saadc_callback);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_drv_saadc_channel_init(0, &channel_config_0);
		err_code = nrf_drv_saadc_channel_init(1, &channel_config_1);
		err_code = nrf_drv_saadc_channel_init(2, &channel_config_2);
		err_code = nrf_drv_saadc_channel_init(3, &channel_config_3);
		
    APP_ERROR_CHECK(err_code);

    //err_code = nrf_drv_saadc_buffer_convert(m_buffer_pool, SAMPLES_IN_BUFFER);
    //APP_ERROR_CHECK(err_code);

}

void SignalAdcLoadBuffer(void){
	
//		nrf_drv_saadc_sample();

}

nrf_saadc_value_t SignalAdcReadChannel(uint8_t Channel){

	nrf_saadc_value_t saadc_val;
	nrf_drv_saadc_sample_convert(Channel,&saadc_val);
	
	return saadc_val;
//	//?????
//	return value_buffer[Channel];
//	
}

