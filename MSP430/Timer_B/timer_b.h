/*
 * timer_b.h
 *
 *  Created on: May 19, 2020
 *      Author: Andrew Ruf
 */

#ifndef MSP430_TIMER_B_TIMER_B_H_
#define MSP430_TIMER_B_TIMER_B_H_

//Include standard library headers
#include "stdbool.h"

#include "driverlib.h"

#define MAX_TIMER_VALUE                 0xFFFF

enum Timer_B_Mode {
    STOP        = 0,
    UP          = 1,
    CONTINUOUS  = 2,
    UP_DOWN     = 3
};

enum Timer_B_CC_Mode {
    CAPTURE     = 0,
    COMPARE     = 1
};

/*! \struct Timer_B_CC_Config
    \brief Structure used to configure Capture/Compare registers within the Timer_B module.
 */

typedef struct {
    enum Timer_B_CC_Mode modeSelect;                /*!< Configure selected Capture/Compare Register to be either CAPTURE (input) or COMPARE (output) */
    uint16_t baseAddress;
    union Timer_B_CC_config_param
    {
        Timer_B_initCaptureModeParam cap_param;
        Timer_B_initCompareModeParam comp_param;
    } Timer_B_CC_config_param;


} Timer_B_CC_Config;

/*! \struct Timer_B_CC_Config
    \brief Structure used to configure the Timer_B module.
 */

typedef struct Timer_B_Config{
    enum Timer_B_Mode mode;

    union Timer_B_config_param
    {
        Timer_B_initUpModeParam up_param;
        Timer_B_initUpDownModeParam up_down_param;
        Timer_B_initContinuousModeParam cont_param;
    } Timer_B_config_param;
} Timer_B_Config;


void ConfigureTimerB(const Timer_B_Config * config, uint16_t baseAddress);
void ConfigureCCModes(const Timer_B_CC_Config * cc_configs, uint8_t num_configs);

#endif /* MSP430_TIMER_B_TIMER_B_H_ */
