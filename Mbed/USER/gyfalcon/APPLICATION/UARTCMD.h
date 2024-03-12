#ifndef _UARTCMD_H_
#define _UARTCMD_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "nrf.h"
#include "nrf_gpio.h"
#include "app_uart.h"
#include "nrf_uart.h"
#include "app_error.h"
#include "nrf_delay.h"
#include "nrf_uarte.h"
#include "board.h"


/********************************PARAMETER**************************************************/
#ifdef  BOARD_PROJECT
#define DEFAULT_RX_PIN  	NRF_GPIO_PIN_MAP(1,10)
#define DEFAULT_TX_PIN  	NRF_GPIO_PIN_MAP(1,3)
#define DEFAULT_CTS_PIN  	NRF_GPIO_PIN_MAP(0,7)
#define DEFAULT_RTS_PIN  	NRF_GPIO_PIN_MAP(0,25)
#endif

#ifdef	BOARD_EXPER
#define DEFAULT_RX_PIN  	NRF_GPIO_PIN_MAP(0,8)
#define DEFAULT_TX_PIN  	NRF_GPIO_PIN_MAP(0,6)
#define DEFAULT_CTS_PIN  	NRF_GPIO_PIN_MAP(0,7)
#define DEFAULT_RTS_PIN  	NRF_GPIO_PIN_MAP(0,25)
#endif

#define DEFAULT_BAUDRATE	NRF_UART_BAUDRATE_9600


#define UART_HWFC APP_UART_FLOW_CONTROL_DISABLED

#define MAX_TEST_DATA_BYTES     (15U)
#define DEFAULT_UART_TX_BUF_SIZE 512
#define DEFAULT_UART_RX_BUF_SIZE 512

extern app_uart_comm_params_t comm_params;

void uart_error_handle(app_uart_evt_t * p_event);


/***************************************************************
  *  @brief     Config Uart Parameters
  *  @param     pin numbers and ctrl flags
  *  @note      if user want to replace default UART ,This 
								function must be used befor begin the default com
  *  @Sampleusage:     NULL
 **************************************************************/

void ComUartConfig(uint32_t RX_PIN , uint32_t TX_PIN , uint32_t RTS_PIN , \
										uint32_t CTS_PIN ,app_uart_flow_control_t flow_control,\
										bool use_parity,uint32_t BAUDRATE);

/***************************************************************
  *  @brief     open Uart 
  *  @param     NULL
  *  @note      NULL
  *  @Sample usage:     NULL
 **************************************************************/
void ComUartBegin(void);

uint8_t ComUartRead(void);

#endif