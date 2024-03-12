/*
 * @C++ FILES: 
 * @Descripttion: 
 * @version: 
 * @Author: TheiiKu
 * @Date: 2023-11-30 18:57:53
 * @LastEditors: TheiiKu
 * @LastEditTime: 2023-12-27 21:40:38
 * @afterAnnotation: CRATED IN JLU SENSOR LAB
 */

/**
* @file     	board.c
* @brief		GYRFALCON SYSTEM BOARD API
* @details	    READ BOARD.h TO GET INTERFACES PROVIDED FOR CUSTOM DEVELOPMENT
* @author		Tianyi Gu   guty22@mails.jlu.edu.cn
*							    theiiku@foxmail.com
* @date		    2023 / December / 15th 
* @version	    v1.1 
* @par Copyright(c): 2023	Tianyi Gu all right reserved	
* @par History:     2023 / Nov / 30th v1.0      +ADD BASIC I/O TEST AND PERIPHERAL INIT  API 

                    2023 / Dec / 15th v1.1      +ADD ANALOG SIGNAL MEASURMENT API 
                                                +ADD CPU TEMP VIEWER API 
                                                +ADD JSON PROTOCOL API
                                                +ADD SSD1306 GUI & START ANIMATION API 
										
										2024/ Jan	/  4th	V1.2			+ADD AVERAGE FILTER	FOR ADC SIGNAL								
																								+ADD CURRENT ALARM API
																								-REMOVE DOUBLE BUFFER SAADC CONVERTER
																								-REMOVE ADC CHANNEL 0 , 2 , 3 , 7  ON BOARD																								
*	version: author, date, desc\n
*/
#include <stdint.h>
#include <string.h>
#include "nrf.h"
#include "app_error.h"

#include "ble.h"
#include "ble_err.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_advertising.h"

#include "nrf_ble_gatt.h"
#include "nrf_ble_qwr.h"
#include "nrf_pwr_mgmt.h"

#include "board.h"
#include "iic.h"
#include "oled.h"
#include "ChipTemp.h"
#include "BoardADC.h"
#include "UARTCMD.h" 
#include "led.h"
#include "buzzer.h"
#include "GUI.h" 
#include "app_timer.h"

#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh_ble.h"

#include "ble_conn_params.h"

#include "peer_manager.h"
#include "peer_manager_handler.h"

#include "fds.h"

#include "nordic_common.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "protocol.h"

#include "app_timer.h"
#include "nrf_temp.h"


#define APP_BLE_CONN_CFG_TAG            1 



/*--------------------------HARDWARE  MACRO--------------------------------------------------*/
//BOARD ADC PIN MAP 
#define CURRENT_OBS     0
#define SENSOR_CH1		1
#define SENSOR_CH2		2
#define SENSOR_CH3		3

//BIOARD ANALOG CONSTANT
#define SAMPLE_RES		1
#define VOLTAGE_REF		2.5
#define ADC_FILTER_REPEAT 10
float ALARM_THRESHOLD = 0.35;


/*--------------------------HARDWARE  MACRO-------------------------------------------------*/



/*--------------------------SOFTWARE  MACRO-------------------------------------------------*/
//SYSTEM SAMPLE INTERVAL
#define SAMPLE_INTERVAL_MS APP_TIMER_TICKS(1000)
#define ALARM_INTERVAL_MS APP_TIMER_TICKS(500)
//SYSTEM TIMER
APP_TIMER_DEF(sys_update);
APP_TIMER_DEF(SYSTEM_ANIMATION);

bool COMM_CTRL_FLAG = true;
/*--------------------------SOFTWARE  MACRO-------------------------------------------------*/


/*--------------------------BUFFER FUNCTION-------------------------------------------------*/

struct BoardMeasurement Buffer_Measurement;

/*--------------------------BUFFER FUNCTION-------------------------------------------------*/



/*--------------------------HANDEL FUNCTION-------------------------------------------------*/

//SYSTEM TIMER
void SystemUpdate();

//void SystemAnimation();


/*--------------------------HANDEL FUNCTION-------------------------------------------------*/



void BoardCopyrghtPrint(void){

    NRF_LOG_INFO("******HARDWARE INFO******");
    NRF_LOG_INFO( VERSION );
    NRF_LOG_INFO( BOARDNAME);
    NRF_LOG_INFO( AUTHOR  );    
    NRF_LOG_INFO( COPYRIGHT  );    
    

}




uint8_t SelfCheckRNG(void)
{
	uint8_t value;
	NRF_RNG->CONFIG=1;       
	NRF_RNG->TASKS_START=1;   
	NRF_RNG->EVENTS_VALRDY=0; 
	while(NRF_RNG->EVENTS_VALRDY==0){} 
	value=NRF_RNG->VALUE;              
	NRF_RNG->TASKS_STOP=1;             
	NRF_RNG->INTENCLR=0;               
	NRF_RNG->CONFIG=0;                 
	return value;
}

void SelfCheckInfo(char *Info){
    OLED_ShowString(10, 6, Info, 1);
}

void SelfCheckUART(){
    for (size_t i = 0; i < 5; i++)
    {   
		SendJosnMsg( TEST , "TESTING", NODECODE ,HOST ,SLAVE );
    }
    OLED_CLS();
}

void SelfCheckDebug(){
    for (size_t i = 0; i < 5; i++)
    {   
        SelfCheckInfo("Debug Checking....");
        OLED_ShowString(10 , i ,"send : " ,1 );
        OLED_ShowNum(50, i, SelfCheckRNG() , 3 , 1);
        NRF_LOG_DEBUG("Get rand num %d" ,SelfCheckRNG());
        nrf_delay_ms(1000);
        
    }
    SelfCheckInfo("Comm Finish !    ");
}
void SelfCheckOled(){
    OLED_ShowString(20, 0, "Peripheral Test ", 1);
    OLED_ShowString(10, 1, "Checking OLED      ", 1);
    SelfCheckInfo("Checking Oled ...");
    nrf_delay_ms(2000);
    OLED_CLS();
    
    for (size_t i = 0; i < 8; i++)
    {   
        OLED_ShowString(10, i, "TEST OLED", 1);
        OLED_ShowString(64, i, "TEST OLED", 1);
        nrf_delay_ms(500);
        
    }
    OLED_Fill(0xff);
    nrf_delay_ms(1000);
    OLED_CLS();
    OLED_ShowString(20, 0, "Peripheral Test ", 1);
    OLED_ShowString(10, 2, "OLED Checked", 1);
}


void SelfCheckLED(){
    SelfCheckInfo("Checking LED ...  ");
    DirectLedOn(LED_ALARM) ;
    DirectLedOn(LED_DIRECT) ;
    nrf_delay_ms(1000);
    DirectLedOff(LED_ALARM) ;
    DirectLedOff(LED_DIRECT) ;
    OLED_ShowString(10, 3, "LED  Checked", 1);
}

void SelfCheckBuzzer(){
    SelfCheckInfo("Checking Buzzer ...");
    Buzzer_On();
    nrf_delay_ms(500);
    Buzzer_Off();
    nrf_delay_ms(500);
    Buzzer_On();
    nrf_delay_ms(200);
    Buzzer_Off();
    nrf_delay_ms(200);
    
    OLED_ShowString(10, 4, "Buzzer Checked", 1);

}


float ADC2Float(uint8_t channel){	
	float value;
	for(int i =0;i<ADC_FILTER_REPEAT;i++){
		value += (float)SignalAdcReadChannel(channel)* 3.6 /4096 *1000 ;
	}
	
	return value/ADC_FILTER_REPEAT;
}

void BoardBuzzerAlarmOn(void){
	nrf_gpio_cfg_output(BUZZER_PIN);
	nrf_gpio_cfg_output(LED_DIRECT);
		nrf_gpio_pin_toggle(BUZZER_PIN);
		nrf_gpio_pin_toggle(LED_DIRECT);
}


void BoardBuzzerAlarmOff(void){
	nrf_gpio_cfg_output(BUZZER_PIN);
	nrf_gpio_cfg_output(LED_ALARM);
		nrf_gpio_pin_clear(BUZZER_PIN);
		nrf_gpio_pin_clear(LED_DIRECT);
}
void BoardCheckCurrent(){
	if(Buffer_Measurement.Current > ALARM_THRESHOLD){
	BoardBuzzerAlarmOn();
	}else{
	BoardBuzzerAlarmOff();
	}
}

void BoardMeasureSignal(void){
//    Buffer_Measurement.Current   = 1;
//    Buffer_Measurement.Channel_1 = 2;
//    Buffer_Measurement.Channel_2 = 3;
//    Buffer_Measurement.Channel_3 = 4;
		SignalAdcLoadBuffer();
    Buffer_Measurement.Current   = ADC2Float(CURRENT_OBS)/SAMPLE_RES;
    Buffer_Measurement.Channel_1 = ADC2Float(SENSOR_CH1);
    Buffer_Measurement.Channel_2 = ADC2Float(SENSOR_CH2);
    Buffer_Measurement.Channel_3 = ADC2Float(SENSOR_CH3);
		BoardCheckCurrent();
}

void BoardMeasureCPUtemp(void){

    int temp; 
    sd_temp_get(&temp);
		Buffer_Measurement.CPUTemp = temp/4;

}


void BoardMeasureUpdate(void){
    BoardMeasureSignal();
    BoardMeasureCPUtemp();
}

void BoardMeasureCleanBuffer(){
    Buffer_Measurement.CPUTemp     = 0 ;
    Buffer_Measurement.Current     = 0 ;
    Buffer_Measurement.Channel_1   = 0 ; 
    Buffer_Measurement.Channel_2   = 0 ; 
    Buffer_Measurement.Channel_3   = 0 ; 
}

void BoardMeasureSendBuffer(){
    BoardMeasureUpdate();
	#ifdef OLED_AVAILABLE
    GUISetMeasure(Buffer_Measurement.CPUTemp,
                  Buffer_Measurement.Current,
                  Buffer_Measurement.Channel_1,
                  Buffer_Measurement.Channel_2,
                  Buffer_Measurement.Channel_3);
	#endif
    //todo : add a protocol function here   
		if(COMM_CTRL_FLAG){
				SendJsonMsgSensorValue(1,Buffer_Measurement.Channel_1 );
				SendJsonMsgSensorValue(2,Buffer_Measurement.Channel_2 );
				SendJsonMsgSensorValue(3,Buffer_Measurement.Channel_3 );
				
				}
SendJsonMsgCPUTemp(Buffer_Measurement.CPUTemp);
}


void SystemUpdate(){
	BoardMeasureSendBuffer();

}
void SystemAnimation(){
	
}

void BoardTimerReg(){
			app_timer_init();
			app_timer_create(&sys_update, APP_TIMER_MODE_REPEATED, SystemUpdate);
			//app_timer_create(&SYSTEM_ANIMATION, APP_TIMER_MODE_REPEATED, SystemAnimation);
}

void BoardTimerStart(){
		app_timer_start(sys_update, APP_TIMER_TICKS(1000), NULL);
		//app_timer_start(SYSTEM_ANIMATION, APP_TIMER_TICKS(1000), NULL);

}

void BoardTimerStop(){
		app_timer_stop(sys_update);
}

void BoardTimerInit(){
		BoardTimerReg();
		BoardTimerStart();
}

static void BoardBleStackInit(void)
{		 nrf_delay_ms(500);
    ret_code_t err_code;

    err_code = nrf_sdh_enable_request();
    APP_ERROR_CHECK(err_code);

    // Configure the BLE stack using the default settings.
    // Fetch the start address of the application RAM.
    uint32_t ram_start = 0;
    err_code = nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &ram_start);
    APP_ERROR_CHECK(err_code);

    // Enable BLE stack.
    err_code = nrf_sdh_ble_enable(&ram_start);
    APP_ERROR_CHECK(err_code);

    // Register a handler for BLE events.
    //NRF_SDH_BLE_OBSERVER(m_ble_observer, APP_BLE_OBSERVER_PRIO, ble_evt_handler, NULL);
}

void BoardInit(void){
				

		
    NRF_LOG_INFO("--------------------SYSTEM INIT----------------------");
    BoardCopyrghtPrint();
    NRF_LOG_INFO("******Peripheral INIT******")                   ;
		I2C_INIT ();//INIT I2C IN SYSTEM
	
		#ifdef OLED_AVAILABLE
       OLED_Init();//INIT I2C OLED
		#endif
    NRF_LOG_DEBUG("I2C DEVICES INIT FINISHED ");
                                                                                                                                                       
   InitChipTemp();//INIT CHIP TEMP SERVICE 
    SignalAdcInit(); //INIT ADC SERVICE   
    NRF_LOG_DEBUG("SOC INIT FINISHED ");

    ComUartBegin(); //uart open

    NRF_LOG_DEBUG("COMMUNICATE DEVICE INIT FINISHED ");
		NRF_LOG_DEBUG("ChipTemp INIT FINISHED ");
    NRF_LOG_DEBUG("BOARD INIT FINISHED ");
	
    NRF_LOG_INFO("******STACK INIT******")       ;
		
		BoardBleStackInit();
		NRF_LOG_DEBUG("BLE STACK INITED ");
		BoardTimerInit();
		NRF_LOG_DEBUG("RTC TIMERS SETED ");
		
	NRF_LOG_INFO("--------------------SYSTEM INIT----------------------");
	
	//debug
}
void BoardSelfCheck(void){
		BoardTimerStop();
    //Communication Test
    SelfCheckUART();
		nrf_delay_ms(500);
//    SelfCheckDebug();
//    nrf_delay_ms(1000);

    OLED_CLS();
    //Peripheral Test 
    SelfCheckOled();
    SelfCheckLED();
    SelfCheckBuzzer();
    SelfCheckInfo("Peripheral finish !  ");
    nrf_delay_ms(1000);
    //Signal Test
		OLED_CLS();
		BoardTimerStart();
	
}
