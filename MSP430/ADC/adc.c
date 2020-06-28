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
    // Init ADC clock and sample hold source
    ADC_init(baseAddress, adc_config->sampleHoldSourceSelect,
             adc_config->clockSource,
             adc_config->clockDivider);

    //Set Resolution
    ADC_setResolution(baseAddress, adc_config->resolution);


    // Sampling Time
    ADC_setupSamplingTimer(baseAddress,
                adc_config->clockCycleHoldCount,
                adc_config->multipleConversionEnable);

    //ADC data format
    ADC_setDataReadBackFormat(baseAddress, adc_config->readBackFormat);

    //Sampling Rate
    ADC_setReferenceBufferSamplingRate(baseAddress, adc_config->refBufferSamplingRate);

    //Enable interrupts
    ADC_enableInterrupt(baseAddress, adc_config->interruptMask);

    //Enable
    ADC_enable(baseAddress);

}
