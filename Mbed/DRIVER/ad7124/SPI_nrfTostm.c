#include "SPI_nrfTostm.h"
#include "nrf_drv_spi.h"
#include "board_pinmap.h"


#define GPIO_PIN_SET	1
#define GPIO_PIN_RESET	0 

static const nrf_drv_spi_t spi = NRF_DRV_SPI_INSTANCE(SPI_INSTANCE);  /**< SPI instance. */

static volatile bool spi_xfer_done;  /**< Flag used to indicate that SPI instance completed the transfer. */

void spi_event_handler(nrf_drv_spi_evt_t const* p_event,void* p_context) {//NRF52840 EZDMA INTERFACE 

}



void uart_cmd_handler() {//NRF52840 uart cmd interfasce 


}




/********************************************************
* Function name £ºinsert_hhistory
* Description        : Insert to bd_host_history
* Parameter         £º
* @ipsql            SQL statement
* @host_level        Risk level
* @total            The total number of risk
* @t_id            task id
* @t_uuid            task uuid
* @ipaddr            target ipaddr
* @end_time        task end time
* Return          £ºNULL
**********************************************************/

void NRF_SPI_Init() {//SPI init func used to repalce STM init func 
	nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
	spi_config.ss_pin = 0;
	//defined in board_pinmap.h
	spi_config.miso_pin = BOARD_SPI_MISO_PIN;
	spi_config.mosi_pin = BOARD_SPI_MOSI_PIN;
	spi_config.sck_pin = BOARD_SPI_SCK_PIN;
	//config cs pin 
	//spi_config.ss_pin = NRF_DRV_SPI_PIN_NOT_USED;

	APP_ERROR_CHECK(nrf_drv_spi_init(&spi, &spi_config, spi_event_handler, NULL));
}




void HAL_GPIO_WritePin(uint32_t Port, uint32_t GPIO_Pin, bool pinstate) {//write GPIO used to replace STM32 HAL_GPIO
	uint32_t pin_number = NRF_GPIO_PIN_MAP(Port, GPIO_Pin);
	
	if (pinstate == GPIO_PIN_SET ) {
		nrf_gpio_pin_set(pin_number);
	}
	if (pinstate == GPIO_PIN_RESET ) {
		nrf_gpio_pin_clear(pin_number);
	}

}

void HAL_GPIO_TogglePin(uint32_t Port, uint32_t GPIO_Pin) {
	uint32_t pin_number = NRF_GPIO_PIN_MAP(Port, GPIO_Pin);
	nrf_gpio_pin_toggle(pin_number);
}

ret_code_t HAL_SPI_TransmitReceive(nrf_drv_spi_t const* const p_instance, uint8_t* pTxData, uint8_t* pRxData, uint16_t Size, uint32_t Timeout){

	uint8_t TxLenth = 0;
	
	//get lenth of * pTxData 
	while (*pTxData)
	{
		pTxData++;
		TxLenth++;
	}
	ret_code_t err_code = nrf_drv_spi_transfer(&p_instance, pTxData, TxLenth, pRxData, Size);
	return ret_code_t;

}


void HAL_Delay(uint32_t ms) {
	nrf_delay_ms(ms);
};

