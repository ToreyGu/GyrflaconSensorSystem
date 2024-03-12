#include "button.h"
#include "app_timer.h"

#include "LED.h"

//创建按键定时器


APP_TIMER_DEF (TIMER_DEBOUNCE);
//中断返回值
static uint8_t BUTTON_IRQ_Value = 0 ;  




//超时函数入口
static void IRQ_TIMER_DEBOUNCE_CALLBACK_TASK(void * p_context);

//按键回调函数
static void IRQ_BUTTON_CALLBACK_TASK(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action);



void IOButtonInit(void){
		
		app_timer_init();
    ret_code_t errCode = nrf_drv_gpiote_init();                                         // GPIOE驱动初始化，如有其它GPIO中断只调用一次
		APP_ERROR_CHECK(errCode);
		nrf_drv_gpiote_in_config_t inConfig =GPIOTE_CONFIG_IN_SENSE_HITOLO(true);         // 双边沿中断触发
		inConfig.pull = NRF_GPIO_PIN_PULLUP;																								// 默认上拉
		//inConfig.sense = NRF_GPIOTE_POLARITY_TOGGLE;
	
		#ifdef BUTTON_1
		
		errCode = nrf_drv_gpiote_in_init(BUTTON_1, &inConfig, IRQ_BUTTON_CALLBACK_TASK);
		nrf_drv_gpiote_in_event_enable(BUTTON_1, true); 
		#endif
	
		
	#ifdef BUTTON_2
	

		errCode = nrf_drv_gpiote_in_init(BUTTON_2, &inConfig, IRQ_BUTTON_CALLBACK_TASK);
		nrf_drv_gpiote_in_event_enable(BUTTON_2, true); 
		#endif
	
		#ifdef BUTTON_3
		errCode = nrf_drv_gpiote_in_init(BUTTON_3, &inConfig, IRQ_BUTTON_CALLBACK_TASK);
		nrf_drv_gpiote_in_event_enable(BUTTON_3, true); 
    #endif 
		
		#ifdef BUTTON_4
		errCode = nrf_drv_gpiote_in_init(BUTTON_4, &inConfig, IRQ_BUTTON_CALLBACK_TASK);
		nrf_drv_gpiote_in_event_enable(BUTTON_4, true); 
		#endif
		
		 ret_code_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

		
		APP_ERROR_CHECK(errCode);
		
		app_timer_create(&TIMER_DEBOUNCE,APP_TIMER_MODE_SINGLE_SHOT,IRQ_TIMER_DEBOUNCE_CALLBACK_TASK);
		printf("timer created");
}

//超时函数入口
static void IRQ_BUTTON_CALLBACK_TASK(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
	{
		
		BUTTON_IRQ_Value = 0 ;
		
		
		if(nrf_gpio_pin_read(BUTTON_1) == BUTTON_OFF)                                 
    {
		printf("button 1" );
		app_timer_start(TIMER_DEBOUNCE,APP_TIMER_TICKS(50) ,NULL);	
		printf("timer start");
    BUTTON_IRQ_Value |= BUTTON_1_IRQ_VAL ; 
		
    }	
		
		if(nrf_gpio_pin_read(BUTTON_2) == BUTTON_OFF)                                  
    {
			
			printf("button 2" );
        BUTTON_IRQ_Value |= BUTTON_2_IRQ_VAL ;                                                  
    }

	

		
		if(nrf_gpio_pin_read(BUTTON_3) == BUTTON_OFF)                                   
    {
			
			printf("button 3" );
        BUTTON_IRQ_Value |= BUTTON_3_IRQ_VAL ;                                               
    };
		

		if(nrf_gpio_pin_read(BUTTON_4) == BUTTON_OFF) 
    {
			printf("button 4" );
        BUTTON_IRQ_Value |= BUTTON_4_IRQ_VAL ;   
    }
		

		//app_timer_start(TIMER_DEBOUNCE,BUTTON_DEBOUNCE_DELAY_MS,NULL);


}

//按键回调函数
static void IRQ_TIMER_DEBOUNCE_CALLBACK_TASK(void * p_context){
	//UNUSED_PARAMETER(TIMER_DEBOUNCE);

		printf("timer");
//		#ifdef BUTTON_1
//		printf("timer");
//		if(nrf_gpio_pin_read(BUTTON_1) ==BUTTON_OFF)                                 
//		{
//			BUTTON_IRQ_Value |= BUTTON_1_IRQ_VAL ;                                               
//		}
//		#endif
//		
//		#ifdef BUTTON_2
//		
//		if(nrf_gpio_pin_read(BUTTON_2) == BUTTON_OFF)                                  
//    {
//        BUTTON_IRQ_Value |= BUTTON_2_IRQ_VAL ;                                                  
//    }
//		#endif
//	
//	
//		#ifdef BUTTON_3
//		
//		if(nrf_gpio_pin_read(BUTTON_3) == BUTTON_OFF)                                   
//    {
//        BUTTON_IRQ_Value |= BUTTON_3_IRQ_VAL ;                                               
//    };
//		
//		#endif

//		#ifdef BUTTON_4
//		if(nrf_gpio_pin_read(BUTTON_1) == BUTTON_OFF) 
//    {
//			
//			DirectLedOn(17);
//        BUTTON_IRQ_Value |= BUTTON_4_IRQ_VAL ;   
//    }
//		#endif
//		
//		
//		if(BUTTON_IRQ_Value & BUTTON_1_IRQ_VAL)
//    {
//        printf("1");
//			
//    }
//		
//		
//		if(BUTTON_IRQ_Value & BUTTON_2_IRQ_VAL)
//    {
//      DirectLedFlashSpeedH(17);
//    }
//		
//		if(BUTTON_IRQ_Value & BUTTON_3_IRQ_VAL)
//		{
//				DirectLedFlashSpeedH(17);
//				
//		}
//		
//		if(BUTTON_IRQ_Value & BUTTON_3_IRQ_VAL)
//		{
//				DirectLedFlashSpeedH(17);
//				
//		}
	//app_timer_stop(TIMER_DEBOUNCE);
}

