/*
 * adc.c
 *
 * adc.c contains implementation to initialize the ADC modules and use them
 *
 *  Created on: May 16, 2020
 *      Author: Andrew Ruf
 */

//Include standard library headers
#include <stdbool.h>


//Include MSP430Ware Driver Header
#include "driverlib.h"

//Include header file for functions to implement
#include "adc.h"

void ConfigureADC(const ADC_Config * adc_config, uint16_t baseAddress)
{
    //ADC_init(baseAddress, adc_config->, clockSourceSelect, clockSourceDivider)
}
