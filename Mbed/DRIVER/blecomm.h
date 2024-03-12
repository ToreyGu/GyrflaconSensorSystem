//#ifndef	_BLECOMM_H
//#define	_BLECOMM_H

//#include <stdint.h>
//#include <string.h>
//#include "nordic_common.h"
//#include "nrf.h"
//#include "app_error.h"
//#include "ble.h"
//#include "ble_err.h"
//#include "ble_hci.h"
//#include "ble_srv_common.h"
//#include "ble_advdata.h"
//#include "ble_advertising.h"
//#include "ble_bas.h"
//#include "ble_rscs.h"
//#include "ble_dis.h"
//#include "ble_conn_params.h"
////#include "sensorsim.h"
//#include "nrf_sdh.h"
//#include "nrf_sdh_soc.h"
//#include "nrf_sdh_ble.h"
//#include "app_timer.h"
//#include "peer_manager.h"
//#include "peer_manager_handler.h"
//#include "bsp_btn_ble.h"
//#include "fds.h"
//#include "ble_conn_state.h"
//#include "nrf_ble_gatt.h"
//#include "nrf_ble_qwr.h"
//#include "nrf_pwr_mgmt.h"

//#include "nrf_log.h"
//#include "nrf_log_ctrl.h"
//#include "nrf_log_default_backends.h"


//#define DEVICE_NAME                     "ARTICANA" /**< Name of device. Will be included in the advertising data. */

//#define APP_ADV_INTERVAL                40                                      /**< The advertising interval (in units of 0.625 ms. This value corresponds to 25 ms). */

//#define APP_ADV_DURATION                18000                                   /**< The advertising duration (180 seconds) in units of 10 milliseconds. */

//#define APP_BLE_OBSERVER_PRIO           3                                       /**< Application's BLE observer priority. You shouldn't need to modify this value. */
//#define APP_BLE_CONN_CFG_TAG            1                                       /**< A tag identifying the SoftDevice BLE configuration. */

//#define BATTERY_LEVEL_MEAS_INTERVAL     APP_TIMER_TICKS(2000)                   /**< Battery level measurement interval (ticks). */
//#define MIN_BATTERY_LEVEL               81                                      /**< Minimum battery level as returned by the simulated measurement function. */
//#define MAX_BATTERY_LEVEL               100                                     /**< Maximum battery level as returned by the simulated measurement function. */
//#define BATTERY_LEVEL_INCREMENT         1                                       /**< Value by which the battery level is incremented/decremented for each call to the simulated measurement function. */

//#define SPEED_AND_CADENCE_MEAS_INTERVAL 1000                                    /**< Speed and cadence measurement interval (milliseconds). */

//#define MIN_SPEED_MPS                   0.5                                     /**< Minimum speed in meters per second for use in the simulated measurement function. */
//#define MAX_SPEED_MPS                   6.5                                     /**< Maximum speed in meters per second for use in the simulated measurement function. */
//#define SPEED_MPS_INCREMENT             1.5                                     /**< Value by which speed is incremented/decremented for each call to the simulated measurement function. */
//#define MIN_RUNNING_SPEED               3                                       /**< speed threshold to set the running bit. */

//#define MIN_CADENCE_RPM                 40                                      /**< Minimum cadence in revolutions per minute for use in the simulated measurement function. */
//#define MAX_CADENCE_RPM                 160                                     /**< Maximum cadence in revolutions per minute for use in the simulated measurement function. */
//#define CADENCE_RPM_INCREMENT           20                                      /**< Value by which cadence is incremented/decremented in the simulated measurement function. */

//#define MIN_STRIDE_LENGTH               20                                      /**< Minimum stride length in decimeter for use in the simulated measurement function. */
//#define MAX_STRIDE_LENGTH               125                                     /**< Maximum stride length in decimeter for use in the simulated measurement function. */
//#define STRIDE_LENGTH_INCREMENT         5                                       /**< Value by which stride length is incremented/decremented in the simulated measurement function. */

//#define MIN_CONN_INTERVAL               MSEC_TO_UNITS(500, UNIT_1_25_MS)        /**< Minimum acceptable connection interval (0.5 seconds). */
//#define MAX_CONN_INTERVAL               MSEC_TO_UNITS(1000, UNIT_1_25_MS)       /**< Maximum acceptable connection interval (1 second). */
//#define SLAVE_LATENCY                   0                                       /**< Slave latency. */
//#define CONN_SUP_TIMEOUT                MSEC_TO_UNITS(4000, UNIT_10_MS)         /**< Connection supervisory timeout (4 seconds). */

//#define FIRST_CONN_PARAMS_UPDATE_DELAY  APP_TIMER_TICKS(5000)                   /**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (5 seconds). */
//#define NEXT_CONN_PARAMS_UPDATE_DELAY   APP_TIMER_TICKS(30000)                  /**< Time between each call to sd_ble_gap_conn_param_update after the first call (30 seconds). */
//#define MAX_CONN_PARAMS_UPDATE_COUNT    3                                       /**< Number of attempts before giving up the connection parameter negotiation. */

//#define SEC_PARAM_BOND                  1                                       /**< Perform bonding. */
//#define SEC_PARAM_MITM                  0                                       /**< Man In The Middle protection not required. */
//#define SEC_PARAM_LESC                  0                                       /**< LE Secure Connections not enabled. */
//#define SEC_PARAM_KEYPRESS              0                                       /**< Keypress notifications not enabled. */
//#define SEC_PARAM_IO_CAPABILITIES       BLE_GAP_IO_CAPS_NONE                    /**< No I/O capabilities. */
//#define SEC_PARAM_OOB                   0                                       /**< Out Of Band data not available. */
//#define SEC_PARAM_MIN_KEY_SIZE          7                                       /**< Minimum encryption key size. */
//#define SEC_PARAM_MAX_KEY_SIZE          16                                      /**< Maximum encryption key size. */

//#define DEAD_BEEF                       0xDEADBEEF                              /**< 填充用的无意义数字Value used as error code on stack dump, can be used to identify stack location on stack unwind. */

//#define APP_FEATURE_NOT_SUPPORTED       BLE_GATT_STATUS_ATTERR_APP_BEGIN + 2    /**< Reply when unsupported features are requested. */

///**
// * @defgroup ble_dis_config Configuration for Device Information Service.
// * @brief Example characteristic values used for Device Information Service. Will be passed to Device Information Service.
// * @{
// */
//#define BLE_DIS_MANUFACTURER_NAME       "College of Electronic Science and Engineering, Jilin University"                   /**< Manufacturer Name String. */
//#define BLE_DIS_MODEL_NUMBER            "ARTICANA FOR GAS SENSOR"                                 /**< Model Number String. */
//#define BLE_DIS_SERIAL_NUMBER           "T0139836"                              /**< Serial Number String. */
//#define BLE_DIS_HW_REVISION             "2023.11"                               /**< Hardware Revision String. */
//#define BLE_DIS_FW_REVISION             "23.11.v2"                                 /**< Firmware Revision String. */
//#define BLE_DIS_SW_REVISION             "23.11.v2"                                 /**< Software Revision String. */
//#define BLE_DIS_MANUFACTURER_ID         0x0000000059                            /**< Manufacturer ID for System ID. */
//#define BLE_DIS_OU_ID                   0x123456                                /**< Organizationally unique ID for System ID. */
//#define BLE_DIS_CERT_LIST               {0x00, 0x01, 0x02, 0x03}                /**< IEEE 11073-20601 Regulatory Certification Data List. */
//#define BLE_DIS_VENDOR_ID               0x0059                                  /**< Vendor ID for PnP ID. */
//#define BLE_DIS_PRODUCT_ID              0x0001                                  /**< Product ID for PnP ID. */
//#define BLE_DIS_PRODUCT_VERSION         0x0002                                  /**< Product Version for PnP ID. */


//APP_TIMER_DEF(m_battery_timer_id);                                              /**< Battery timer. */
//APP_TIMER_DEF(m_rsc_meas_timer_id);                                             /**< RSC measurement timer. */
//BLE_BAS_DEF(m_bas);                                                             /**< Structure used to identify the battery service. */
//BLE_RSCS_DEF(m_rscs);                                                           /**< Structure used to identify the running speed and cadence service. */
//NRF_BLE_GATT_DEF(m_gatt);                                                       /**< GATT module instance. */
//BLE_ADVERTISING_DEF(m_advertising);                                             /**< Advertising module instance. */
//NRF_BLE_QWR_DEF(m_qwr);                                                         /**< Context for the Queued Write module.*/


//static uint16_t          m_conn_handle = BLE_CONN_HANDLE_INVALID;               /**< Handle of the current connection. */


//static ble_uuid_t m_adv_uuids[] =                                               /**< Universally unique service identifiers. */
//{
//    {BLE_UUID_RUNNING_SPEED_AND_CADENCE,    BLE_UUID_TYPE_BLE},
//    {BLE_UUID_BATTERY_SERVICE,              BLE_UUID_TYPE_BLE},
//    {BLE_UUID_DEVICE_INFORMATION_SERVICE,   BLE_UUID_TYPE_BLE}
//};

//void advertising_start(bool erase_bonds);
//void advertising_init(void);
//#endif