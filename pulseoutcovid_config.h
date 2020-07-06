/*
 * pulseoutcovid_config.h
 *
 *  Created on: May 16, 2020
 *      Author: andre
 */

#ifndef PULSEOUTCOVID_CONFIG_H_
#define PULSEOUTCOVID_CONFIG_H_

#include "MSP430/Clock/clock.h"
#include "MSP430/IO/io.h"
#include "MSP430/Timer_B/timer_b.h"
#include "MSP430/ADC/adc.h"
#include "MSP430/SAC/sac.h"

#define DEBUG 0



// Clock Tree Globals
const ClockTree tree = {
     .Dco =
     {
         .clocksource = CS_REFOCLK_SELECT,
         .FLLdivider = CS_CLOCK_DIVIDER_1,
         .outputfrequency = DCO_24MHZ,
         .reference_ratio = 732,
     },
     .Aclk =
     {
         .clocksource = CS_REFOCLK_SELECT,
         .divider = CS_CLOCK_DIVIDER_1,
     },
     .Mclk =
     {
         .clocksource = CS_DCOCLKDIV_SELECT,
         .divider = CS_CLOCK_DIVIDER_1,
     },
     .SMclk =
     {
         .divider = CS_CLOCK_DIVIDER_1,
         .enable = true,
     },
};

//Timer_B Globals
#define TIMER_B_SRC_CLK                     TIMER_B_CLOCKSOURCE_SMCLK
#define TIMER_B_SRC_CLK_PERIOD_HZ           24000000
#define TIMER_B_CLK_DIV                     TIMER_B_CLOCKSOURCE_DIVIDER_6
#define TIMER_B_CLK_DIV_VAL                 6

#define TIMER_B_LED_PERIOD_US                   1000
#define TIMER_B_RED_IR_LED_ON_US                333
#define TIMER_B_BETWEEN_RED_IR_PULSES_US        333


const Timer_B_Config timer_b_config =
{
     .mode                                  = UP,
     .Timer_B_config_param                  =
     {
          .up_param       =
          {
               .clockSource                             = TIMER_B_SRC_CLK,
               .clockSourceDivider                      = TIMER_B_CLK_DIV,
               .timerPeriod                             = TIMER_B_LED_PERIOD_US * (TIMER_B_SRC_CLK_PERIOD_HZ / TIMER_B_CLK_DIV_VAL / 1e6),
               .timerInterruptEnable_TBIE               = TIMER_B_TBIE_INTERRUPT_DISABLE,
               .captureCompareInterruptEnable_CCR0_CCIE = TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE,
               .timerClear                              = TIMER_B_DO_CLEAR,
               .startTimer                              = false,
          },
     },
};

#define NUM_CC_CONFIGS     2
const Timer_B_CC_Config CC_configs [] = {


    {
         .modeSelect                    = COMPARE,
         .baseAddress                   = TB2_BASE,
         .Timer_B_CC_config_param       =
         {
             .comp_param                =
             {
                  .compareRegister          = TIMER_B_CAPTURECOMPARE_REGISTER_1,
                  .compareInterruptEnable   = TIMER_B_CAPTURECOMPARE_INTERRUPT_ENABLE,
                  .compareOutputMode        = TIMER_B_OUTPUTMODE_RESET_SET,
                  .compareValue             = TIMER_B_RED_IR_LED_ON_US * (TIMER_B_SRC_CLK_PERIOD_HZ / TIMER_B_CLK_DIV_VAL / 1e6),
             },
         },
    },


    {
         .modeSelect                    = COMPARE,
         .baseAddress                   = TB1_BASE,
         .Timer_B_CC_config_param       =
         {
             .comp_param                =
             {
                  .compareRegister          = TIMER_B_CAPTURECOMPARE_REGISTER_1,
                  .compareInterruptEnable   = TIMER_B_CAPTURECOMPARE_INTERRUPT_ENABLE,
                  .compareOutputMode        = TIMER_B_OUTPUTMODE_SET_RESET,
                  .compareValue             = (TIMER_B_RED_IR_LED_ON_US + TIMER_B_BETWEEN_RED_IR_PULSES_US) * (TIMER_B_SRC_CLK_PERIOD_HZ / TIMER_B_CLK_DIV_VAL / 1e6),

             },
         },
    },
};

// ADC Globals
const ADC_Config adc_config =
{
     .sampleHoldSourceSelect        = ADC_SAMPLEHOLDSOURCE_SC,
     .clockSource                   = ADC_CLOCKSOURCE_SMCLK,
     .clockDivider                  = ADC_CLOCKDIVIDER_6,
     .resolution                    = ADC_RESOLUTION_12BIT,
     .interruptMask                 = 0,
     .readBackFormat                = ADC_UNSIGNED_BINARY,
     .clockCycleHoldCount           = ADC_CYCLEHOLD_16_CYCLES,
     .multipleConversionEnable      = ADC_MULTIPLESAMPLESDISABLE,
     .refBufferSamplingRate         = ADC_MAXSAMPLINGRATE_200KSPS
};

//SAC Configs
//For SAC 0 and SAC 2
const SAC sac_LED_config =
{
     .sacMode       = DAC,

     .oaPosInput    = SAC_OA_POSITIVE_INPUT_SOURCE_DAC,
     .oaNegInput    = SAC_OA_NEGATIVE_INPUT_SOURCE_PGA,
     .oaPowerMode   = SAC_OA_POWER_MODE_HIGH_SPEED_HIGH_POWER,

     .pgaGainMode   = SAC_PGA_MODE_BUFFER,
     .pgaGain       = SAC_PGA_GAIN_BIT0,

     .dacRefVoltage = SAC_DAC_PRIMARY_REFERENCE,
     .dacLoad       = SAC_DAC_LOAD_DACDAT_WRITTEN,
     .dacInitData   = 0x0000,
};

const SAC sac_1_config =
{
     .sacMode       = PGA,
     .oaPowerMode   = SAC_OA_POWER_MODE_HIGH_SPEED_HIGH_POWER,
     .oaPosInput    = SAC_OA_POSITIVE_INPUT_SOURCE_EXTERNAL,
     .oaNegInput    = SAC_OA_NEGATIVE_INPUT_SOURCE_EXTERNAL,

     .pgaGainMode   = SAC_PGA_MODE_BUFFER,
     .pgaGain       = SAC_PGA_GAIN_BIT0,               // - 1 Gain

};

const SAC sac_3_config =
{
     .sacMode       = DAC,
     .oaPowerMode   = SAC_OA_POWER_MODE_HIGH_SPEED_HIGH_POWER,
     .oaPosInput    = SAC_OA_POSITIVE_INPUT_SOURCE_DAC,
     .oaNegInput    = SAC_OA_NEGATIVE_INPUT_SOURCE_EXTERNAL,

     .pgaGainMode   = SAC_PGA_MODE_INVERTING,
     .pgaGain       = SAC_PGA_GAIN_BIT2,                // -8 Gain

     .dacRefVoltage = SAC_DAC_PRIMARY_REFERENCE,
     .dacLoad       = SAC_DAC_LOAD_DACDAT_WRITTEN,
     .dacInitData   = 273                               // ~220 mv offset

};


// IO Globals
#define NUM_CONFIG_PINS     23
const Pin pins[] = {
    // SAC2 Output Red LED DAC Current Control
    // Pin 2
    {
         .port      = GPIO_PORT_P3,
         .pin       = GPIO_PIN1,
         .direction = OUTPUT,
         .mode      = GPIO_TERNARY_MODULE_FUNCTION,
         .enable    = true,
    },

    // MCLK Test Point
    // Pin 3
    {
         .port      = GPIO_PORT_P3,
         .pin       = GPIO_PIN0,
         .direction = OUTPUT,
         .mode      = GPIO_PRIMARY_MODULE_FUNCTION,
         .enable    = false,
    },

    // A3 Power Sample
    // Pin 4
    {
        .port       = GPIO_PORT_P1,
        .pin        = GPIO_PIN3,
        .direction  = INPUT,
        .mode       = GPIO_TERNARY_MODULE_FUNCTION,
        .enable    = true,
    },

    // SAC0 Output IR DAC Current Control
    // Pin 6
    {
        .port       = GPIO_PORT_P1,
        .pin        = GPIO_PIN1,
        .direction  = OUTPUT,
        .mode       = GPIO_TERNARY_MODULE_FUNCTION,
        .enable    = true,
    },

    // A0 Temp Probe
    // Pin 7
    {
        .port       = GPIO_PORT_P1,
        .pin        = GPIO_PIN0,
        .direction  = INPUT,
        .mode       = GPIO_TERNARY_MODULE_FUNCTION,
        .enable    = false,
    },

    // P2.7 Red Indicator LED On/Off
    // Pin 12
    {
#define RED_IND_LED_PORT           GPIO_PORT_P2
#define RED_IND_LED_PIN            GPIO_PIN7

        .port       = GPIO_PORT_P2,
        .pin        = GPIO_PIN7,
        .direction  = OUTPUT,
        .mode       = 0,
        .enable    = true,
    },

    // P2.6 Yellow Indicator LED On/Off
    // Pin 13
    {
#define YELLOW_IND_LED_PORT        GPIO_PORT_P2
#define YELLOW_IND_LED_PIN            GPIO_PIN6
        .port       = GPIO_PORT_P2,
        .pin        = GPIO_PIN6,
        .direction  = OUTPUT,
        .mode       = 0,
        .enable    = true,
    },

    // P2.5 Green LED Indicator LED On/Off
    // Pin 14
    {
#define GREEN_IND_LED_PORT         GPIO_PORT_P2
#define GREEN_IND_LED_PIN            GPIO_PIN5
        .port       = GPIO_PORT_P2,
        .pin        = GPIO_PIN5,
        .direction  = OUTPUT,
        .mode       = 0,
        .enable    = true,
    },

    // P2.4 ADC Alert Indicator LED On/Off
    // Pin 15
    {
        .port       = GPIO_PORT_P2,
        .pin        = GPIO_PIN4,
        .direction  = OUTPUT,
        .mode       = 0,
        .enable    = true,
    },

    // P4.7 UCB1SCL I2C SCL
    // Pin 16
    {
        .port       = GPIO_PORT_P4,
        .pin        = GPIO_PIN7,
        .direction  = EITHER,
        .mode       = GPIO_PRIMARY_MODULE_FUNCTION,
        .enable    = false,
    },

    // P4.6 UCB1SDA I2C SDA
    // Pin 17
    {
        .port       = GPIO_PORT_P4,
        .pin        = GPIO_PIN6,
        .direction  = EITHER,
        .mode       = GPIO_PRIMARY_MODULE_FUNCTION,
        .enable    = false,
    },

    // P4.3 UCA1TXD UART TX
    // Pin 20
    {
        .port       = GPIO_PORT_P4,
        .pin        = GPIO_PIN3,
        .direction  = OUTPUT,
        .mode       = GPIO_PRIMARY_MODULE_FUNCTION,
        .enable    = true,
    },

    // P4.2 UCA1RXD UART RX
    // Pin 21
    {
        .port       = GPIO_PORT_P4,
        .pin        = GPIO_PIN2,
        .direction  = INPUT,
        .mode       = GPIO_PRIMARY_MODULE_FUNCTION,
        .enable    = true,
    },

    // P2.1 TB2.1 Red LED PWM
    // Pin 26
    {
        .port       = GPIO_PORT_P5,
        .pin        = GPIO_PIN0,
        .direction  = OUTPUT,
        .mode       = GPIO_PRIMARY_MODULE_FUNCTION,
        .enable    = true,
    },

    // P2.0 TB1.1 IR LED PWM
    // Pin 27
    {
        .port       = GPIO_PORT_P2,
        .pin        = GPIO_PIN0,
        .direction  = OUTPUT,
        .mode       = GPIO_PRIMARY_MODULE_FUNCTION,
        .enable    = true,
    },

    // P1.7 SAC1 OA1+, TIA Pos Input
    // Pin 28
    {
        .port       = GPIO_PORT_P1,
        .pin        = GPIO_PIN7,
        .direction  = INPUT,
        .mode       = GPIO_TERNARY_MODULE_FUNCTION,
        .enable    = true,
    },

    // P1.6 SAC1 OA1- TIA Neg Input
    // Pin 29
    {
        .port       = GPIO_PORT_P1,
        .pin        = GPIO_PIN6,
        .direction  = INPUT,
        .mode       = GPIO_TERNARY_MODULE_FUNCTION,
        .enable    = true,
    },

    // P1.5 SAC1 OA1O TIA Output
    // Pin 30
    {
        .port       = GPIO_PORT_P1,
        .pin        = GPIO_PIN5,
        .direction  = OUTPUT,
        .mode       = GPIO_TERNARY_MODULE_FUNCTION,
        .enable    = true,
    },

    // P1.4 A4 DC Offset Sample
    // Pin 31
    {
        .port       = GPIO_PORT_P1,
        .pin        = GPIO_PIN4,
        .direction  = INPUT,
        .mode       = GPIO_TERNARY_MODULE_FUNCTION,
        .enable    = true,
    },

    // P3.7 SAC3 OA3+, GSA Pos Input
    // Pin 32
    {
        .port       = GPIO_PORT_P3,
        .pin        = GPIO_PIN7,
        .direction  = INPUT,
        .mode       = GPIO_TERNARY_MODULE_FUNCTION,
        .enable    = false,
    },

    // P3.6 SAC3 OA3- GSA Neg Input
    // Pin 33
    {
        .port       = GPIO_PORT_P3,
        .pin        = GPIO_PIN6,
        .direction  = INPUT,
        .mode       = GPIO_TERNARY_MODULE_FUNCTION,
        .enable    = true,
    },

    // P3.5 SAC3 OA3O GSA Output
    // Pin 34
    {
        .port       = GPIO_PORT_P3,
        .pin        = GPIO_PIN5,
        .direction  = OUTPUT,
        .mode       = GPIO_TERNARY_MODULE_FUNCTION,
        .enable    = true,
    },

    // P5.1 A9 AC Sample
    // Pin 36
    {
        .port       = GPIO_PORT_P5,
        .pin        = GPIO_PIN1,
        .direction  = INPUT,
        .mode       = GPIO_TERNARY_MODULE_FUNCTION,
        .enable     = true,
    },

};




#endif /* PULSEOUTCOVID_CONFIG_H_ */
