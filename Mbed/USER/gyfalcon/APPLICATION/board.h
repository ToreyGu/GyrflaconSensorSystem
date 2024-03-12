/*
 * @C++ FILES: 
 * @Descripttion: 
 * @version: 
 * @Author: TheiiKu
 * @Date: 2023-11-30 18:57:40
 * @LastEditors: TheiiKu
 * @LastEditTime: 2023-12-01 21:48:58
 * @afterAnnotation: CRATED IN JLU SENSOR LAB
 */
#ifndef	_BOARD_H
#define	_BOARD_H

#include "nrf.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"

#define BOARDNAME "BOARD MODEL : Gyrflacon Community Version v24H1.1.0" 
#define AUTHOR    "DESIGNED BY : Tianyi Gu"
#define COPYRIGHT "COPYRIGHT   : Tianyi Gu ALL RIGHTS RESERVED "
#define VERSION   "COMMUNITY VERSION , RESEARCH USE ONLY " 

//baord version 
//#define BOARD_EXPER
#define BOARD_PROJECT
//oled ctrl
#define OLED_AVAILABLE



//#define SCL NRF_GPIO_PIN_MAP(0,2)
//#define SDA NRF_GPIO_PIN_MAP(0,31)

#define BUTTON_USER NRF_GPIO_PIN_MAP(0,21)


#define BUZZER_PIN NRF_GPIO_PIN_MAP(1,13)


#define LED_ALARM   NRF_GPIO_PIN_MAP(1,11)
#define LED_DIRECT  NRF_GPIO_PIN_MAP(1,12)



struct BoardMeasurement{
		int   CPUTemp;
		float Current;
		float	Channel_1;
		float Channel_2;
	  float Channel_3;
};


extern float ALARM_THRESHOLD ;
extern bool  COMM_CTRL_FLAG;
	
void BoardInit(void);
void BoardSelfCheck(void);
void BoardMeasureSignal(void);
void BoardMeasureSend(void);
void SendJsonMsgCPUTemp(float Temp);
void timers_init(void);
void application_timers_start(void);

#endif