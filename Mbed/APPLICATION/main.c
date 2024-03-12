/**
 *
 *  Copyright (C) Waveshare November 2018.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

 
#include "nrf.h"


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "app_uart.h"
#include "app_error.h"
#include "nrf_delay.h"

#include "nrf_uart.h"
#include "nrf_uarte.h"

#include "led.h"
#include "uart.h"

#include "ADC.h"
#include "button.h"


/**
 * @brief Function for main application entry.
 */
int main(void)
{
	ComUartBegin();
IOButtonInit();
SignalAdcInit();    
DirectLedOn(NRF_GPIO_PIN_MAP(0,18));

//ConfigBoardInit();
//IOButtonInit();
	printf("Across the Great Wall, we can reach every corner in the world !\r\n");
		nrf_delay_ms(500);
		while(1){
			DirectLedFlashSpeedH(18);
			printf("WE GET %.4f \r\n",SignalAdcReadChannel(6)*3.6/1024);

		nrf_delay_ms(100);

	}
	
}

