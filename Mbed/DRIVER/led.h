#ifndef _LED_H
#define _LED_H
#include "nrf.h"
#include "nrf_gpio.h"



#define LED_BLE NRF_GPIO_PIN_MAP(1,11)
#define LED_COM NRF_GPIO_PIN_MAP(1,12)

/********************************PARAMETER**************************************************/
#define HIGHSPEED 200
#define MIDSPEED	500
#define LOWSPEED	800


/*********************************** CONFIG ***********************************************/
#define LED_FLAG 1
//LED WORKING MODE
// 1 for High level enabled
// 0 for Low level enabled



void DirectLedInit(uint32_t led_number);

void  DirectLedOn(uint32_t led_number);

void  DirectLedOff(uint32_t led_number);

void  DirectLedFlashSpeedL(uint32_t led_number);
	
void	DirectLedFlashSpeedM(uint32_t led_number);
	
void	DirectLedFlashSpeedH(uint32_t led_number);

void	DirectLedOnBle(void);
void	DirectLedOffBle(void);

void	DirectLedOnCom(void);
void  DirectLedOffCom(void);



#endif
