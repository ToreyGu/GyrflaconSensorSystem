#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "UART_nrfTostm.h"
#include "app_uart.h"
#include "nrf_uart.h"
#include "board_pinmap.h"


#define	BufferLength 16
#define	CMD_LENGTH 7
#define	DATA_LENGTH 4


char CmdBuffer[BufferLength];
volatile unsigned char CmdBufferCounter = 0;

void uart_cmd_bufferinit() {//init uart buffer 
	memset(CmdBuffer, '\0', sizeof(CmdBuffer));
	CmdBufferCounter = 0;
}

void uart_cmd_handel() { //handel func for uart cmd
	char CMD_CODE[CMD_LENGTH];
	char CMD_DATA[DATA_LENGTH];

	memcpy(CMD_CODE, CmdBuffer, CMD_LENGTH);
	memcpy(CMD_DATA, CmdBuffer + CMD_LENGTH + 1, DATA_LENGTH);
	////CMD "LEDTOGG"
	//if (strcmp(CMD_CODE, CMD_LED_TOGGLE) == 0) {
	//	nrf_gpio_pin_toggle(NRF_GPIO_PIN_MAP(1, 11));
	//}
	////CMD "SELCHEK"
	//if (strcmp(CMD_CODE, CMD_SELF_CHECK) == 0) {
	//	BoardSelfCheck();
	//}
	////CMD "CHGVALU+0.500"
	//if (strcmp(CMD_CODE, CMD_CHANGE_VALUE) == 0) {
	//	ALARM_THRESHOLD = atof(CMD_DATA);
	//}
	////CMD "STACOMM"
	//if (strcmp(CMD_CODE, CMD_START_COMM) == 0) {
	//	COMM_CTRL_FLAG = true;
	//	uartCmdBufferInit();
	//}

	////CMD "STPCOMM"
	//if (strcmp(CMD_CODE, CMD_STOP_COMM) == 0) {
	//	COMM_CTRL_FLAG = false;
	//}
}


void uart_error_handel(app_uart_evt_t* p_event) {
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
		CmdBuffer[CmdBufferCounter] = dat;
		CmdBufferCounter++;
	}
	else if (p_event->evt_type == APP_UART_TX_EMPTY)
	{
		uart_cmd_handel();
		uart_cmd_bufferinit();
		//nrf_gpio_pin_toggle(NRF_GPIO_PIN_MAP(1,11));//LED flash WHEN DO NOT HAVE DATA INPUT
	}



}
app_uart_comm_params_t comm_params =
{
	BOARD_UART_RX_PIN,
	BOARD_UART_TX_PIN,
	0,
	0,
	false,
	BOARD_UART_BAUDRATE
};



void uart_event_handler(app_uart_evt_t* p_event)
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
	{
		app_uart_get(&dat);
		CmdBuffer[CmdBufferCounter] = dat;
		CmdBufferCounter++;
	}
	else if (p_event->evt_type == APP_UART_TX_EMPTY)
	{
		uart_cmd_handel();
		uart_cmd_bufferinit();
		//nrf_gpio_pin_toggle(NRF_GPIO_PIN_MAP(1,11));//LED flash WHEN DO NOT HAVE DATA INPUT

	}

}


void NRF_UART_Init() {

	uint32_t err_code;
	APP_UART_FIFO_INIT(&comm_params, DEFAULT_UART_RX_BUF_SIZE, DEFAULT_UART_TX_BUF_SIZE, \
		uart_error_handel, APP_IRQ_PRIORITY_LOWEST, err_code);
	APP_ERROR_CHECK(err_code);

}

uint32_t HAL_UART_Receive(uint8_t* p_byte) {
	return app_uart_get(uint8_t* p_byte);
}
