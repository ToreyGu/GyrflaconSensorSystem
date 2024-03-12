#ifndef UART_NRFTOSTM_H__
#define UART_NRFTOSTM_H__

#define DEFAULT_UART_TX_BUF_SIZE 512
#define DEFAULT_UART_RX_BUF_SIZE 512
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "nrf.h"
uint32_t HAL_UART_Receive(uint8_t* p_byte);

#endif