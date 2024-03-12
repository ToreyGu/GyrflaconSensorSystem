/*
 * @C++ FILES: 
 * @Descripttion: 
 * @version: 
 * @Author: TheiiKu
 * @Date: 2023-11-30 19:07:26
 * @LastEditors: TheiiKu
 * @LastEditTime: 2023-12-01 19:33:41
 * @afterAnnotation: CRATED IN JLU SENSOR LAB
 */
 
// #define HOST        "gHost"
//#define SLAVE       "gSlave"
//#define NODECODE    "0"
//#define REGISTER    "REG"
//#define SENSORVALUE "VAL"
//#define CHIPTEMP    "CHT"
//#define ALARM       "ALA"
//#define TEST				"TST"

 //COMMUNICATE WITH JSON DATA 
#include "protocol.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#ifndef LOG_OBSERVER
#define LOG_OBSERVER
#endif
//{"cmd":"value","data":1,"nodecode":88,"sendto":"gyfalconHost","from":"nodecode"}
//{%ccmd%c:%cvalue%c,%cdata%c:%s,%cnodecode%c:%s,%csendto%c:%c%s%c,%cfrom%c:%c%s%c}



#define MAX_OBJECT_LEN 16

static char quote = '"';
void SendJosnMsg(char* cmd , char* data , char* nodecode ,char* sendto ,char* from ){
        char buffer[128];
		sprintf(buffer,"{%ccmd%c:%c%s%c,%cdata%c:%s,%cnodecode%c:%s,%csendto%c:%c%s%c,%cfrom%c:%c%s%c}\r\n" ,
                quote,quote,quote,cmd,quote,
                quote,quote,data,
                quote,quote,nodecode,
                quote,quote,quote,sendto,quote,
                quote,quote,quote,from,quote);
		//open logobserver
		#ifdef LOG_OBSERVER
		NRF_LOG_INFO("%s" ,NRF_LOG_PUSH(buffer));
		#endif
		printf("%s" ,buffer);
}

void SendJsonMsgSensorValue(int Channel ,float Value ){
        char CHANNEL_BUFFER[MAX_OBJECT_LEN];
        char VAL_BUFFER[MAX_OBJECT_LEN]; 
        sprintf(CHANNEL_BUFFER , "%s%d" , SENSORVALUE , Channel);
        sprintf(VAL_BUFFER , "%.4f" , Value);
        SendJosnMsg( CHANNEL_BUFFER,  VAL_BUFFER , NODECODE , HOST  ,SLAVE );
}

void SendJsonMsgCPUTemp(float Temp){
				char TEMP_BUFFER[MAX_OBJECT_LEN]; 
				sprintf(TEMP_BUFFER , "%.1f" , Temp);
				SendJosnMsg( CHIPTEMP,  TEMP_BUFFER , NODECODE , HOST  ,SLAVE );
}