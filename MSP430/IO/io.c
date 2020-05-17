/*
 * io.c
 *
 * io.c contains implementation to initialize pins and set
 *
 *  Created on: May 16, 2020
 *      Author: Andrew Ruf
 */

//Include standard library headers
#include <stdbool.h>


//Include MSP430Ware Driver Header
#include "driverlib.h"

//Include header file for functions to implement
#include "io.h"


static inline void ConfigurePin(Pin * pin)
{
    if(pin->enable){
        if(pin->mode != 0){
            if(pin->direction == INPUT){
                GPIO_setAsPeripheralModuleFunctionInputPin(pin->port,
                                                           pin->pin,
                                                           pin->mode);
            }
            else{
                GPIO_setAsPeripheralModuleFunctionOutputPin(pin->port,
                                                            pin->pin,
                                                            pin->mode);
            }
        }
        else{
            if(pin->direction == INPUT){
                GPIO_setAsInputPin(pin->port, pin->pin);
            }
            else{
                GPIO_setAsInputPin(pin->port, pin->pin);
            }
        }
    }
}


void ConfigurePins(Pin * pins, uint8_t number_pins)
{

    int i = 0;
    for(i = 0; i < number_pins; i++){
        ConfigurePin(&pins[i]);
    }

}



