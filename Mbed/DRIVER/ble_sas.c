/*********************************************************************
 * INCLUDES
 */
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(BLE_SAS)
#include "ble_srv_common.h"

#include "ble_sas.h"


#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

//#include "common.h"

static void sas_on_write(Sas_t *pSas, ble_evt_t const *pBleEvent);
static void sas_on_connect(Sas_t *pSas, ble_evt_t const *pBleEvent);
static void sas_on_disconnect(Sas_t *pSas, ble_evt_t const *pBleEvent);
/*********************************************************************
 * LOCAL VARIABLES
 */


/*********************************************************************
 * EXTERN FUNCTIONS
 */
// ������������
extern void Sas_HandleCharValue(uint16_t connHandle, uint8_t charId, Sas_t *pSas,
                                            const uint8_t *pCharValue, uint16_t length);
// 
/*********************************************************************
 * PUBLIC FUNCTIONS
 */
/**
 @brief ���ALM Init Profile����
 @param ��
 @return NRF_SUCCESS - �ɹ�������ֵ - ʧ��
*/
uint32_t Sas_AddService(Sas_t *pSas)
{   
    SasCallback_t sasCallback = {0};
    sasCallback.sasCharWriteHandler = Sas_HandleCharValue; // �����ⲿ������Ӧ�ò㴦������ֵ

    return Sas_RegisterAppCallback(pSas, &sasCallback);
}

/**
 @brief ע��Ӧ�ó���ص�������ֻ�����������һ��
 @param pSas -[out] ALM��ʼ������ṹ��
 @param pAppCallback -[in] ָ��Ӧ�ó���Ļص�
 @return NRF_SUCCESS - �ɹ�������ֵ - ʧ��
*/
uint32_t Sas_RegisterAppCallback(Sas_t *pSas, const SasCallback_t *pAppCallback)
{
    uint32_t errCode;
    ble_uuid_t bleUuid;
    ble_add_char_params_t addCharParams;

    // ��ʼ������ṹ��
    pSas->sasCharWriteHandler = pAppCallback->sasCharWriteHandler;

    /*--------------------- ���� ---------------------*/
    ble_uuid128_t baseUuid = {SAS_UUID_BASE};
    errCode = sd_ble_uuid_vs_add(&baseUuid, &pSas->uuidType);
    VERIFY_SUCCESS(errCode);

    bleUuid.type = pSas->uuidType;
    bleUuid.uuid = SAS_UUID_SERVICE;

    errCode = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &bleUuid, &pSas->serviceHandle);
    VERIFY_SUCCESS(errCode);

    /*--------------------- ����1 ---------------------*/
    memset(&addCharParams, 0, sizeof(addCharParams));
    addCharParams.uuid              = SAS_UUID_CHAR1;
    addCharParams.uuid_type         = pSas->uuidType;
    addCharParams.init_len          = sizeof(uint8_t);
    addCharParams.max_len           = SAS_CHAR1_LEN;                             // ��������
    addCharParams.char_props.read   = 1;                                                    // �ɶ�
    addCharParams.char_props.write  = 1;                                                    // ��д
    addCharParams.char_props.notify = 1;                                                    // ��֪ͨ                              

    addCharParams.read_access       = SEC_OPEN;
    addCharParams.write_access      = SEC_OPEN;
    addCharParams.cccd_write_access = SEC_OPEN;

    errCode = characteristic_add(pSas->serviceHandle, &addCharParams, &pSas->char1Handle);
    if(errCode != NRF_SUCCESS)
    {
        return errCode;
    }

    /*--------------------- ����2 ---------------------*/
    memset(&addCharParams, 0, sizeof(addCharParams));
    addCharParams.uuid             = SAS_UUID_CHAR2;
    addCharParams.uuid_type        = pSas->uuidType;
    addCharParams.init_len         = sizeof(uint8_t);
    addCharParams.max_len          = SAS_CHAR2_LEN;                              // ��������
    addCharParams.char_props.read  = 1;                                                     // �ɶ�
    addCharParams.char_props.write = 1;                                                     // ��д
    addCharParams.char_props.notify = 1;   
    addCharParams.read_access  = SEC_OPEN;
    addCharParams.write_access = SEC_OPEN;
    addCharParams.cccd_write_access = SEC_OPEN;
    errCode = characteristic_add(pSas->serviceHandle, &addCharParams, &pSas->char2Handle);
    if(errCode != NRF_SUCCESS)
    {
        return errCode;
    }
    
    /*--------------------- ����3 ---------------------*/
    memset(&addCharParams, 0, sizeof(addCharParams));
    addCharParams.uuid             = SAS_UUID_CHAR3;
    addCharParams.uuid_type        = pSas->uuidType;
    addCharParams.init_len         = sizeof(uint8_t);
    addCharParams.max_len          = SAS_CHAR3_LEN;                              // ��������
    addCharParams.char_props.read  = 1;                                                     // �ɶ�
    addCharParams.char_props.write = 1;                                                     // ��д
    addCharParams.char_props.notify = 1;   
    addCharParams.read_access  = SEC_OPEN;
    addCharParams.write_access = SEC_OPEN;
    addCharParams.cccd_write_access = SEC_OPEN;
    errCode = characteristic_add(pSas->serviceHandle, &addCharParams, &pSas->char3Handle);
    if(errCode != NRF_SUCCESS)
    {
        return errCode;
    }
    
    /*--------------------- ����4 ---------------------*/
    memset(&addCharParams, 0, sizeof(addCharParams));
    addCharParams.uuid             = SAS_UUID_CHAR4;
    addCharParams.uuid_type        = pSas->uuidType;
    addCharParams.init_len         = sizeof(uint8_t);
    addCharParams.max_len          = SAS_CHAR4_LEN;                              // ��������
    addCharParams.char_props.read  = 1;                                                     // �ɶ�
    addCharParams.char_props.write = 1;                                                     // ��д
    addCharParams.char_props.notify = 1;   
    addCharParams.read_access  = SEC_OPEN;
    addCharParams.write_access = SEC_OPEN;
    addCharParams.cccd_write_access = SEC_OPEN;
    errCode = characteristic_add(pSas->serviceHandle, &addCharParams, &pSas->char4Handle);
    if(errCode != NRF_SUCCESS)
    {
        return errCode;
    }
    
    return errCode;
}
// 
///**
// @brief ������������Э��ջ��Ӧ���¼�
// @param pBleEvent -[in] ��������Э��ջ���¼�
// @param pContext -[in] ALM��ʼ������ṹ��
// @return ��
//*/
void HandleSasOnBleStackEvent(ble_evt_t const *pBleEvent, void *pContext)
{
    Sas_t *pSas = (Sas_t *)pContext;
    
    switch(pBleEvent->header.evt_id)
    {
		case BLE_GATTS_EVT_WRITE:
			sas_on_write(pSas, pBleEvent);
			NRF_LOG_INFO("BLE_GATTS_EVT_WRITE");
			break;
        case BLE_GAP_EVT_CONNECTED:
            sas_on_connect(pSas, pBleEvent);
			NRF_LOG_INFO("LE_GAP_EVT_CONNECTED");
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            sas_on_disconnect(pSas, pBleEvent);
			NRF_LOG_INFO("LE_GAP_EVT_DISCONNECTED");
            break;

    default:
        // No implementation needed.
        break;
    }
}

/**
 @brief ����֪ͨ����
 @param connHandle -[in] ���Ӿ��
 @param pSas -[in] ALM��ʼ������ṹ��
 @param pData -[in] ֪ͨ����
 @param dataLen -[in] ֪ͨ���ݳ���
 @return NRF_SUCCESS - �ɹ�������ֵ - ʧ��
*/
uint32_t Sas_PushNotifyData(uint16_t connHandle, Sas_t *pSas, uint8_t *pData, uint16_t dataLen)
{
    ble_gatts_hvx_params_t params;
    NRF_LOG_INFO("%d",connHandle);
    if(connHandle == BLE_CONN_HANDLE_INVALID)
    {
        return NRF_ERROR_NOT_FOUND;
    }
    if(dataLen > SAS_CHAR1_LEN)
    {
        return NRF_ERROR_INVALID_PARAM;
    }

    memset(&params, 0, sizeof(params));
    params.type   = BLE_GATT_HVX_NOTIFICATION;
    params.handle = pSas->char1Handle.value_handle;
    params.p_data = pData;
    params.p_len  = &dataLen;

    return sd_ble_gatts_hvx(connHandle, &params);
}


/*********************************************************************
 * LOCAL FUNCTIONS
 */
/**
 @brief д���ԣ���д��֮ǰ��֤��������
 @param pSas -[in] ALM��ʼ������ṹ��
 @param pBleEvent -[in] ��������Э��ջ���¼�
 @return ��
*/
static void sas_on_write(Sas_t *pSas, ble_evt_t const *pBleEvent)
{
    ble_gatts_evt_write_t const *pEventWrite = &pBleEvent->evt.gatts_evt.params.write;
    uint8_t characteristicId;
	NRF_LOG_INFO("RcharacteristicId , %d",pEventWrite->handle);
	NRF_LOG_INFO("1characteristicId , %d",pSas->char1Handle.value_handle);
	NRF_LOG_INFO("2characteristicId , %d",pSas->char2Handle.value_handle);
	NRF_LOG_INFO("3characteristicId , %d",pSas->char3Handle.value_handle);
	NRF_LOG_INFO("4characteristicId , %d",pSas->char4Handle.value_handle);
    /*--------------------- ����1 ---------------------*/
    if((pEventWrite->handle == pSas->char1Handle.value_handle)
        && (pEventWrite->len == SAS_CHAR1_LEN)   
        )
    {	NRF_LOG_INFO("handel1");
        characteristicId = SAS_CHAR1;
        pSas->sasCharWriteHandler(pBleEvent->evt.gap_evt.conn_handle, characteristicId,
                                                        pSas, pEventWrite->data, pEventWrite->len);
    }   
    /*--------------------- ����2 ---------------------*/
    else if((pEventWrite->handle == pSas->char2Handle.value_handle)
        && (pEventWrite->len == SAS_CHAR2_LEN)   
       )
    {NRF_LOG_INFO("handel2");
        characteristicId = SAS_CHAR2;
        pSas->sasCharWriteHandler(pBleEvent->evt.gap_evt.conn_handle, characteristicId,
                                                        pSas, pEventWrite->data, pEventWrite->len);
    }
    /*--------------------- ����3 ---------------------*/
    else if((pEventWrite->handle == pSas->char3Handle.value_handle)
        && (pEventWrite->len == SAS_CHAR3_LEN)   
       )
    {NRF_LOG_INFO("handel3");
        characteristicId = SAS_CHAR3;
        pSas->sasCharWriteHandler(pBleEvent->evt.gap_evt.conn_handle, characteristicId,
                                                        pSas, pEventWrite->data, pEventWrite->len);
    }
    /*--------------------- ����4 ---------------------*/
    else if((pEventWrite->handle == pSas->char4Handle.value_handle)
        && (pEventWrite->len == SAS_CHAR4_LEN)   
       )
    {NRF_LOG_INFO("handel4");
        characteristicId = SAS_CHAR4;
        pSas->sasCharWriteHandler(pBleEvent->evt.gap_evt.conn_handle, characteristicId,
                                                        pSas, pEventWrite->data, pEventWrite->len);
    }
}
static void sas_on_connect(Sas_t *pSas, ble_evt_t const *pBleEvent)
{
	 pSas->conn_handle = pBleEvent->evt.gatts_evt.conn_handle;
}

static void sas_on_disconnect(Sas_t *pSas, ble_evt_t const *pBleEvent)
{
    UNUSED_PARAMETER(pBleEvent);
    pSas->conn_handle = BLE_CONN_HANDLE_INVALID;
}


uint32_t ble_sas_measurement_send(Sas_t *pSas ,uint8_t *DataBuffer ,uint16_t DataLen)
{
    uint32_t err_code;
    ble_gatts_value_t gatts_value;
    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));
    gatts_value.len     = sizeof(uint8_t);
    gatts_value.offset  = 0;
    gatts_value.p_value = DataBuffer;
    // Update database.
    err_code = sd_ble_gatts_value_set(pSas->conn_handle,
                                     pSas->char2Handle.value_handle,
                                      &gatts_value);
    // Send value if connected
    if (pSas->conn_handle != BLE_CONN_HANDLE_INVALID)
    {	
        uint16_t               len;
        uint16_t               hvx_len;
        ble_gatts_hvx_params_t hvx_params;
	
				len = 16;
        //len     = hts_measurement_encode(p_hts, p_hts_meas, encoded_hts_meas);
        hvx_len = len;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = pSas->char2Handle.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = 0;
        hvx_params.p_len  = &DataLen;
        hvx_params.p_data = DataBuffer;

        err_code = sd_ble_gatts_hvx(pSas->conn_handle, &hvx_params);
			
				NRF_LOG_INFO("sd_ble_gatts_hvx result: %x. \r\n", err_code); 
				NRF_LOG_INFO("handel %d" ,pSas->conn_handle );
				NRF_LOG_INFO("SEND! %d" ,*DataBuffer);
				NRF_LOG_INFO("byte %d" ,DataLen );
        if ((err_code == NRF_SUCCESS) && (hvx_len != len))
        {
            err_code = NRF_ERROR_DATA_SIZE;
        }
    }
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }

    return err_code;
}

#endif // NRF_MODULE_ENABLED(BLE_SAS)



/****************************************************END OF FILE****************************************************/