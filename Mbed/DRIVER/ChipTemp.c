

#include "nrf.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "nrf_temp.h"

//BLESOFTWARE CONFIG
#define BLESOFTWAREON 

int CheckChipTemp(){

    int temp;
            //Start the temperature measurement
    #ifdef BLESOFTWAREON
    temp = sd_temp_get(&temp);
    #else
        /**@note Busy wait while temperature measurement is not finished, 
         * you can skip waiting if you enable interrupt for DATARDY event
         * and read the result in the interrupt. 
         */

    
        //A zero has been given as right argument to operator

        //A zero has been given as right argument to operator

        /**@note Workaround for PAN_028 rev2.0A anomaly 29 - TEMP: 
         *Stop task clears the TEMP register. 
         */
        NRF_TEMP->TASKS_START = 1;
        while (NRF_TEMP->EVENTS_DATARDY == 0)
        {
            // Do nothing.
        }
        //A zero has been given as right argument to operator
        NRF_TEMP->EVENTS_DATARDY = 0;
        temp = (nrf_temp_read() / 4);
        NRF_TEMP->TASKS_STOP = 1; 
    #endif
    return temp;
}

void InitChipTemp(){


    nrf_temp_init();
     
}