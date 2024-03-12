#ifndef	_BOARDADC_H
#define	_BOARDADC_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nrf.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"


void SignalAdcInit(void);
void SignalAdcLoadBuffer(void);
nrf_saadc_value_t SignalAdcReadChannel(uint8_t Channel);

#endif