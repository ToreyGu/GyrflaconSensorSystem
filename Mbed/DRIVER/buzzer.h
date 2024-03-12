#ifndef __BUZZER_H__
#define __BUZZER_H__

#include "nrfx.h"
#include "nrf_gpio.h"

#include "nrf_delay.h"
#define BUZZER_PIN NRF_GPIO_PIN_MAP(1,13)

	#ifdef BUZZER_PIN
	void Buzzer_On(void);
	void Buzzer_Off(void);
	#else
	void Buzzer_On(uint32_t BuzzerPin);
	void Buzzer_Off(uint32_t BuzzerPin);
	#endif

#endif
