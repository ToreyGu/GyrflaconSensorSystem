#include "uart.h"

#include <stdio.h>
#include <string.h>

#include "nrf_uart.h"
#include "app_uart.h"

#include <stdlib.h>
#define BufferLength 16


#define  CMD_DEVICE_INFO  "DEVINFO"
#define  CMD_SELF_CHECK   "SELCHEK"
#define  CMD_CHANGE_VALUE "CHGVALU"
#define  CMD_START_COMM		"STACOMM"
#define  CMD_LED_TOGGLE		"LEDTOGG"
#define  CMD_OLED_TOGGLE	"OLETOGG"


char CmdBuffer[BufferLength] ;
unsigned char CmdBufferCounter = 0 ;

void uartCmdBufferInit(){

	memset(CmdBuffer, '\0', sizeof(CmdBuffer)); 
	CmdBufferCounter = 0 ;
}

void uartCmdHandel(){
			char CMD_Seven_CODE[7];
			memcpy(CMD_Seven_CODE,CmdBuffer,7);;
			
			if(strcmp(CMD_Seven_CODE, CMD_LED_TOGGLE) == 0){
				nrf_gpio_pin_toggle(NRF_GPIO_PIN_MAP(1,11));
			}
			if(strcmp(CMD_Seven_CODE, CMD_LED_TOGGLE) == 0){
				nrf_gpio_pin_toggle(NRF_GPIO_PIN_MAP(1,11));
				
				
			}

}


app_uart_comm_params_t comm_params =
{
    DEFAULT_RX_PIN,
    DEFAULT_TX_PIN,
    DEFAULT_RTS_PIN,
    DEFAULT_CTS_PIN,
    UART_HWFC,
    false,
    DEFAULT_BAUDRATE
};


void uart_error_handle(app_uart_evt_t * p_event)
{
	
	uint8_t dat;
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
			{
					//APP_ERROR_HANDLER(p_event->data.error_communication);
			}
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
			{
					APP_ERROR_HANDLER(p_event->data.error_code);
			}
    else if (p_event->evt_type == APP_UART_DATA_READY)
			{//??????? , ??????
				app_uart_get(&dat); // ????
				app_uart_put(dat); // ????
				CmdBuffer[CmdBufferCounter] = dat;
				CmdBufferCounter++;
			}
    else if (p_event->evt_type == APP_UART_TX_EMPTY) 
				{
					//nrf_gpio_pin_toggle(NRF_GPIO_PIN_MAP(1,11));//LED flash WHEN DO NOT HAVE DATA INPUT
				uartCmdHandel();
					uartCmdBufferInit();
					}
	

}


void ComUartConfig(uint32_t RX_PIN , uint32_t TX_PIN , uint32_t RTS_PIN , \
										uint32_t CTS_PIN ,app_uart_flow_control_t flow_control,\
										bool use_parity,uint32_t BAUDRATE){
		
		comm_params.rx_pin_no 	=		RX_PIN;
		comm_params.tx_pin_no 	=		TX_PIN;
		comm_params.rts_pin_no 	= 	RTS_PIN ;
		comm_params.cts_pin_no  =		CTS_PIN ;
		comm_params.flow_control=		flow_control;
		comm_params.use_parity	=		use_parity;
		comm_params.baud_rate   =		BAUDRATE;	
															
}
										
void ComUartBegin(){
		
		uint32_t err_code;
		APP_UART_FIFO_INIT(&comm_params,DEFAULT_UART_RX_BUF_SIZE,DEFAULT_UART_TX_BUF_SIZE,\
												uart_error_handle,APP_IRQ_PRIORITY_LOWEST,err_code);
		APP_ERROR_CHECK(err_code);
		
}


uint8_t ComUartRead(void){
		uint8_t CharBuffer;
		app_uart_get(&CharBuffer);
		return CharBuffer;
}


