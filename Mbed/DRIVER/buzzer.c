#include "buzzer.h"
	#ifdef BUZZER_PIN
	void Buzzer_On(void)
	{
			nrf_gpio_cfg_output(BUZZER_PIN);
			nrf_gpio_pin_set(BUZZER_PIN);
	 
	}

	void Buzzer_Off(void){
			nrf_gpio_cfg_output(BUZZER_PIN);
			nrf_gpio_pin_clear(BUZZER_PIN);
	}
	#else 
	void Buzzer_On(uint32_t BuzzerPin){
			nrf_gpio_cfg_output(BuzzerPin);
			nrf_gpio_pin_set(BuzzerPin);
	}
	void Buzzer_Off(uint32_t BuzzerPin){
			nrf_gpio_cfg_output(BuzzerPin);
			nrf_gpio_pin_clear(BuzzerPin);
	}
	#endif
	