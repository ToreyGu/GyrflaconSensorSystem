/*
 * @C++ FILES: 
 * @Descripttion: 
 * @version: 
 * @Author: TheiiKu
 * @Date: 2023-11-30 19:10:43
 * @LastEditors: TheiiKu
 * @LastEditTime: 2023-12-01 19:11:07
 * @afterAnnotation: CRATED IN JLU SENSOR LAB
 */
#ifndef	_PROTOCOL_H
#define	_PROTOCOL_H

#define HOST        "gHost"
#define SLAVE       "gSlave"
#define NODECODE    "0"
#define REGISTER    "REG"
#define SENSORVALUE "VAL"
#define CHIPTEMP    "CHT"
#define ALARM       "ALA"
#define TEST				"TST"

//void SendJsonMsg(*uint8_t cmd ,  );
void SendJosnMsg(char* cmd , char* data , char* nodecode ,char* sendto ,char* from );
void SendJsonMsgSensorValue(int Channel ,float Value );


#endif