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

// IO Globals
#define NUM_CONFIG_PINS     23
const Pin pins[] = {
    // SAC2 Output Red LED DAC Current Control
    // Pin 2
    {
         .port      = GPIO_PORT_P3,
         .pin       = GPIO_PIN1,
         .direction = OUTPUT,
         .mode      = 3,
         .enable    = true,
    },

    // MCLK Test Point
    // Pin 3
    {
         .port      = GPIO_PORT_P3,
         .pin       = GPIO_PIN0,
         .direction = OUTPUT,
         .mode      = 1,
         .enable    = false,
    },

    // A3 Power Sample
    // Pin 4
    {
        .port       = GPIO_PORT_P1,
        .pin        = GPIO_PIN3,
        .direction  = INPUT,
        .mode       = 3,
        .enable    = true,
    },

    // SAC0 Output IR DAC Current Control
    // Pin 6
    {
        .port       = GPIO_PORT_P1,
        .pin        = GPIO_PIN1,
        .direction  = OUTPUT,
        .mode       = 3,
        .enable    = true,
    },

    // A0 Temp Probe
    // Pin 7
    {
        .port       = GPIO_PORT_P1,
        .pin        = GPIO_PIN0,
        .direction  = INPUT,
        .mode       = 3,
        .enable    = false,
    },

    // P2.7 Red Indicator LED On/Off
    // Pin 12
    {
        .port       = GPIO_PORT_P2,
        .pin        = GPIO_PIN7,
        .direction  = OUTPUT,
        .mode       = 0,
        .enable    = true,
    },

    // P2.6 Yellow Indicator LED On/Off
    // Pin 13
    {
        .port       = GPIO_PORT_P2,
        .pin        = GPIO_PIN6,
        .direction  = OUTPUT,
        .mode       = 0,
        .enable    = true,
    },

    // P2.5 Green LED Indicator LED On/Off
    // Pin 14
    {
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
        .mode       = 1,
        .enable    = false,
    },

    // P4.6 UCB1SDA I2C SDA
    // Pin 17
    {
        .port       = GPIO_PORT_P4,
        .pin        = GPIO_PIN6,
        .direction  = EITHER,
        .mode       = 1,
        .enable    = false,
    },

    // P4.3 UCA1TXD UART TX
    // Pin 20
    {
        .port       = GPIO_PORT_P4,
        .pin        = GPIO_PIN3,
        .direction  = OUTPUT,
        .mode       = 1,
        .enable    = true,
    },

    // P4.2 UCA1RXD UART RX
    // Pin 21
    {
        .port       = GPIO_PORT_P4,
        .pin        = GPIO_PIN2,
        .direction  = INPUT,
        .mode       = 1,
        .enable    = true,
    },

    // P2.1 TB1.2 Red LED PWM
    // Pin 26
    {
        .port       = GPIO_PORT_P2,
        .pin        = GPIO_PIN1,
        .direction  = OUTPUT,
        .mode       = 1,
        .enable    = true,
    },

    // P2.0 TB1.1 IR LED PWM
    // Pin 27
    {
        .port       = GPIO_PORT_P2,
        .pin        = GPIO_PIN0,
        .direction  = OUTPUT,
        .mode       = 1,
        .enable    = true,
    },

    // P1.7 SAC1 OA1+, TIA Pos Input
    // Pin 28
    {
        .port       = GPIO_PORT_P1,
        .pin        = GPIO_PIN7,
        .direction  = INPUT,
        .mode       = 3,
        .enable    = true,
    },

    // P1.6 SAC1 OA1- TIA Neg Input
    // Pin 29
    {
        .port       = GPIO_PORT_P1,
        .pin        = GPIO_PIN6,
        .direction  = INPUT,
        .mode       = 3,
        .enable    = true,
    },

    // P1.5 SAC1 OA1O TIA Output
    // Pin 30
    {
        .port       = GPIO_PORT_P1,
        .pin        = GPIO_PIN5,
        .direction  = OUTPUT,
        .mode       = 3,
        .enable    = true,
    },

    // P1.4 A4 DC Offset Sample
    // Pin 31
    {
        .port       = GPIO_PORT_P1,
        .pin        = GPIO_PIN4,
        .direction  = INPUT,
        .mode       = 3,
        .enable    = true,
    },

    // P3.7 SAC3 OA3+, GSA Pos Input
    // Pin 32
    {
        .port       = GPIO_PORT_P3,
        .pin        = GPIO_PIN7,
        .direction  = INPUT,
        .mode       = 3,
        .enable    = false,
    },

    // P3.6 SAC3 OA3- GSA Neg Input
    // Pin 33
    {
        .port       = GPIO_PORT_P3,
        .pin        = GPIO_PIN6,
        .direction  = INPUT,
        .mode       = 3,
        .enable    = true,
    },

    // P3.5 SAC3 OA3O GSA Output
    // Pin 34
    {
        .port       = GPIO_PORT_P3,
        .pin        = GPIO_PIN5,
        .direction  = OUTPUT,
        .mode       = 3,
        .enable    = true,
    },

    // P5.1 A9 AC Sample
    // Pin 36
    {
        .port       = GPIO_PORT_P5,
        .pin        = GPIO_PIN1,
        .direction  = INPUT,
        .mode       = 3,
        .enable    = true,
    },

};



#endif /* PULSEOUTCOVID_CONFIG_H_ */
