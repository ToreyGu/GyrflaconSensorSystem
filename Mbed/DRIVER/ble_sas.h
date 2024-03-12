#ifndef _BLE_SAS_H_
#define _BLE_SAS_H_

/*********************************************************************
 * INCLUDES
 */
#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"

//#include "common.h"

/*********************************************************************
 * DEFINITIONS
 */
#ifdef __cplusplus
extern "C" {
#endif
 
#define BLE_SAS_DEF(_name)                       \
static Sas_t _name;                              \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                         \
                     BLE_SAS_BLE_OBSERVER_PRIO,  \
                     HandleSasOnBleStackEvent, &_name)

#define SAS_UUID_BASE        {0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80, \
                                        0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
#define SAS_UUID_SERVICE     BLE_UUID_TYPE_BLE
#define SAS_UUID_CHAR1       0xFEFF
#define SAS_UUID_CHAR2       0xFE00
#define SAS_UUID_CHAR3       0xFE10
#define SAS_UUID_CHAR4       0xFE31

// Profile Parameters
#define SAS_CHAR1            0                               // uint8_t - Profile Characteristic 1 value
#define SAS_CHAR2            1                               // uint8_t - Profile Characteristic 2 value
#define SAS_CHAR3            2                               // uint8_t - Profile Characteristic 3 value
#define SAS_CHAR4            3                               // uint8_t - Profile Characteristic 4 value
#define SAS_CHAR5            4                               // uint8_t - Profile Characteristic 5 value
                                        
// Length of Characteristic in bytes
#define SAS_CHAR1_LEN        20                              // CHAR1 LEN
#define SAS_CHAR2_LEN        20                             // CHAR2 LEN
#define SAS_CHAR3_LEN        20                             // CHAR3 LEN
#define SAS_CHAR4_LEN        20                             // CHAR4 LEN
#define SAS_CHAR5_LEN        20                             // CHAR5 LEN                                        

/*********************************************************************
 * TYPEDEFS
 */
// Forward declaration of the Sas_t type.
typedef struct sasService_s Sas_t;

typedef void (*SasCharWriteHandler_t)(uint16_t connHandle, uint8_t charId, Sas_t *pSas,
                                                const uint8_t *pCharValue, uint8_t length);

/* 
 ALM Init Service init structure.
 This structure contains all options 
 and data needed for initialization of the service.
*/
typedef struct
{
    SasCharWriteHandler_t sasCharWriteHandler;    // Event handler to be called when the Characteristic is written.
} SasCallback_t;

/*
 ALM Init Service structure.
 This structure contains various status information for the service.
*/
struct sasService_s
{
    uint16_t 				 serviceHandle;                                               // Handle of ALM Init Service (as provided by the BLE stack).
    ble_gatts_char_handles_t char1Handle;                               // Handles related to the Characteristic 1.
    ble_gatts_char_handles_t char2Handle;                               // Handles related to the Characteristic 2.
    ble_gatts_char_handles_t char3Handle;                               // Handles related to the Characteristic 3.
    ble_gatts_char_handles_t char4Handle;                               // Handles related to the Characteristic 4.
	uint16_t                 conn_handle;                               /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
	uint8_t 				 uuidType;                                                     // UUID type for the ALM Init Service.
    SasCharWriteHandler_t 	 sasCharWriteHandler;    					// Event handler to be called when the Characteristic is written.
};

/*********************************************************************
 * API FUNCTIONS
 */
uint32_t Sas_AddService(Sas_t *pSas);
uint32_t Sas_RegisterAppCallback(Sas_t *pSas, const SasCallback_t *pAppCallback);
void HandleSasOnBleStackEvent(ble_evt_t const *pBleEvent, void *pContext);
uint32_t Sas_PushNotifyData(uint16_t connHandle, Sas_t *pSas, uint8_t *pData, uint16_t dataLen);
uint32_t ble_sas_measurement_send(Sas_t *pSas ,uint8_t *DataBuffer ,uint16_t DataLen);

#ifdef __cplusplus
}
#endif

#endif /* _ALM_INIT_PROFILE_H_ */