#include "GUI.h"
#include "oled.h"


uint8_t aimation_counter_instrument =1;

void GUISetMeasure(int CPUtemp , float Current ,float Channel_1 ,float Channel_2 , float Channel_3){

	OLED_ShowString(0,0,(uint8_t*)"Sensor1: ",1); 
	OLED_ShowFloat(0,1,Channel_1 ,1);

	OLED_ShowString(0,2,(uint8_t*)"Sensor2: ",1);	
	OLED_ShowFloat(0,3,Channel_2,1);	

	OLED_ShowString(0,4,(uint8_t*)"Sensor3: ",1);
	OLED_ShowFloat(0,5,Channel_3 ,1);

	
	OLED_ShowString(64,0,(uint8_t*)"Current: ",1);
	OLED_ShowFloat(64,1,Current,1);

	OLED_ShowString(64,2,(uint8_t*)"CPU Temp: ",1); 
	OLED_ShowNum(64,3,  CPUtemp ,2,1);

	OLED_ShowString(56,4,(uint8_t*)">>working<< ",1); 
	OLED_ShowString(0,6,(uint8_t*)"GyrflaconSystem",2);
	
switch(aimation_counter_instrument){
		case 1:
			OLED_ShowString(64,5,(uint8_t*)">>",1);
			break;
		case 2:
			OLED_ShowString(64,5,(uint8_t*)">>>>",1);
			break;
		case 3:
			OLED_ShowString(64,5,(uint8_t*)">>>>>>",1);
			break;
		case 4:
			OLED_ShowString(64,5,(uint8_t*)">>>>>>>>",1);
			break;
		default:
			OLED_ShowString(64,5,(uint8_t*)"         ",1);
			aimation_counter_instrument =0;
			break;
	}
	
	aimation_counter_instrument++;

}