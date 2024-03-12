/**
* @file         
* @brief		This is a brief description.
* @details	    This is the detail description.
* @author		author
* @date		    date
* @version	    v1.0
* @par Copyright(c): 	abc corporation
* @par History:         
*	version: author, date, desc\n
*/





#ifndef	_BUTTON_H
#define	_BUTTON_H
#include "nrfx_gpiote.h"
#include "nrf_gpio.h"
#include "nrf_gpiote.h"
#include "nrf_drv_gpiote.h"
#include "app_timer.h"



#define BUTTON_OFF 0
#define BUTTON_ON  1

#define BUTTON_1	NRF_GPIO_PIN_MAP(0,13)
#define BUTTON_2	NRF_GPIO_PIN_MAP(0,14)
#define	BUTTON_3	NRF_GPIO_PIN_MAP(0,15)
#define	BUTTON_4	NRF_GPIO_PIN_MAP(0,16)


//中断值映射

#define BUTTON_1_IRQ_VAL 0x01
#define BUTTON_2_IRQ_VAL 0x02
#define BUTTON_3_IRQ_VAL 0x04
#define BUTTON_4_IRQ_VAL 0x08


//按键软去抖延时
#define BUTTON_DEBOUNCE_DELAY_MS APP_TIMER_TICKS(20)

void IOButtonInit(void);


#endif

