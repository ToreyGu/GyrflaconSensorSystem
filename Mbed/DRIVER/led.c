/**
* @file      	LED.C
* @brief		LED Driver for nrf52 series 
* @details	 	This driver can make led ON/OFF/FLASH
* @author		ToreyGu(GuTianyi)
* @date		    2023 10 25th
* @version	    v1.0
* @par Copyright(c): 	ToreyGu ALL RIGHT RESERVED
* @par History:         
*	version: ToreyGu, 2023 10 25th, V1.0
*/



#include "LED.h"
#include "nrf.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"





/***************************************************************
  *  @brief     make a led on
  *  @param     uint32_t led_number  
  *  @note      You MUST make sure LED_FLAG in LED.h is same as your own board
  *  @Sample 	DirectLedOn(uint32_t LED_BLE NRF_GPIO_PIN_MAP(1,11))
 **************************************************************/

void  DirectLedOn(uint32_t led_number){
	nrf_gpio_cfg_output(led_number);
	if(LED_FLAG){
	nrf_gpio_pin_set(led_number);
	}
	else{
	nrf_gpio_pin_clear(led_number);
	}

}
/***************************************************************
  *  @brief     make a led on
  *  @param     uint32_t led_number  
  *  @note      You MUST make sure LED_FLAG in LED.h is same as your own board
  *  @Sample 	DirectLedOn(uint32_t LED_BLE NRF_GPIO_PIN_MAP(1,11))
 **************************************************************/

void  DirectLedOff(uint32_t led_number){
	nrf_gpio_cfg_output(led_number);
	if(LED_FLAG){
	nrf_gpio_pin_clear(led_number);
	}
	else{
	nrf_gpio_pin_set(led_number);
	}
}


void DirectLedFlashSpeedL(uint32_t led_number){
	nrf_gpio_pin_set(led_number);
	nrf_delay_ms(LOWSPEED);
	nrf_gpio_pin_clear(led_number);
	nrf_delay_ms(LOWSPEED);
}
/***************************************************************
  *  @brief     init a led pin
  *  @param     uint32_t led_number  
  *  @note      null
  *  @Sample 	DirectLedInit(uint32_t LED_BLE NRF_GPIO_PIN_MAP(1,11))
 **************************************************************/

void DirectLedInit(uint32_t led_number){
	
DirectLedOff(led_number);
	
}
void  DirectLedFlashSpeedM(uint32_t led_number){
	nrf_gpio_pin_set(led_number);
	nrf_delay_ms(MIDSPEED);
	nrf_gpio_pin_clear(led_number);
	nrf_delay_ms(MIDSPEED);
}

void  DirectLedFlashSpeedH(uint32_t led_number){

	nrf_gpio_pin_set(led_number);
	nrf_delay_ms(HIGHSPEED);
	nrf_gpio_pin_clear(led_number);
	nrf_delay_ms(HIGHSPEED);}


void	DirectLedOnBle(){
	DirectLedOn(LED_BLE);
/*********************************** DEBUG ***********************************************/
    /**/

	
}
void	DirectLedOffBle(){
	DirectLedOff(LED_BLE);
	
/*********************************** DEBUG ***********************************************/
    /**/
	
}
void	DirectLedOnCom(){
	DirectLedOn(LED_COM);
}
void  DirectLedOffCom(){
	DirectLedOff(LED_COM);
}
