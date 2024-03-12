/********************************************************************************
* @File name: SPI_nrfTostm.h
* @Author: Torey Gu (Gu Tianyi)
* @Version: 1.0
* @Date: 2024-3-06
* @Description: a nrf HAL lib porting to STM 32 HAL lib
********************************************************************************/
#ifndef SPI_NRFTOSTM_H__
#define SPI_NRFTOSTM_H__
#include <string.h>
#include "nrf_drv_spi.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "nrf_drv_spi.h"
#include "board_pinmap.h"
#include "app_uart.h"



void HAL_GPIO_WritePin(uint32_t Port, uint32_t GPIO_Pin, bool pinstate);

void HAL_GPIO_TogglePin(uint32_t Port, uint32_t GPIO_Pin);

uint32_t HAL_SPI_TransmitReceive(nrf_drv_spi_t const* const p_instance, uint8_t* pTxData, uint8_t* pRxData, uint16_t Size, uint32_t Timeout);

void HAL_Delay(uint32_t ms);


#endif