/*
 * adc.h
 *
 * adc.h contains implementation to initialize the ADC modules and use them
 *
 *  Created on: Jun 22, 2020
 *      Author: Andrew Ruf
 */

#ifndef MSP430_ADC_ADC_H_
#define MSP430_ADC_ADC_H_

typedef struct {
    uint16_t    sampleHoldSourceSelect;
    uint8_t     clockSource;
    uint16_t    clockDivider;
    uint16_t    resolution;
    uint16_t    interruptMask;
    uint16_t    readBackFormat;
    uint16_t    clockCycleHoldCount;
    uint16_t    multipleConversionEnable;
    uint16_t    refBufferSamplingRate;

} ADC_Config;

typedef struct {
    uint8_t     inputSource;
    uint8_t     posRefVoltage;
    uint8_t     negRefVoltage;

    uint16_t    conversionSequenceMode;
    bool        blocking;
} ADC_Measurement_Config;

void ConfigureADC(const ADC_Config * adc_config, uint16_t baseAddress);
int16_t ReadADC(ADC_Measurement_Config * config, uint16_t baseAddress);

#endif /* MSP430_ADC_ADC_H_ */
