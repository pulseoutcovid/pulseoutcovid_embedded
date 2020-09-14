/*
 * ISR.c
 *
 *  Created on: Jun 22, 2020
 *      Author: andre
 */

#include <stdio.h>
#include <stdlib.h>

#include "driverlib.h"
#include "pulseoutcovid_config.h"

// IR LED OFF ISR
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_B0_VECTOR
__interrupt void TIMER1_CCR0_IR_LED_OFF_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_B0_VECTOR))) TIMER1_CCR0_IR_LED_ON_ISR (void)
#else
#error Compiler not supported!
#endif
{

    Timer_B_clearCaptureCompareInterrupt(TB1_BASE, TIMER_B_CAPTURECOMPARE_REGISTER_0);
    //GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN7 | GPIO_PIN6 | GPIO_PIN5);
}

// IR LED ON ISR
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_B1_VECTOR
__interrupt void TIMER1_CCR1_IR_LED_ON_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_B1_VECTOR))) TIMER1_CCR0_IR_LED_ON_ISR (void)
#else
#error Compiler not supported!
#endif
{

    Timer_B_clearCaptureCompareInterrupt(TB1_BASE, TIMER_B_CAPTURECOMPARE_REGISTER_1);

    char str[]="\n\r";

    int16_t IR_main = ReadADC(&photodiode_reading_main, ADC_BASE);
    int16_t IR_DC   = ReadADC(&photodiode_reading_dc_offset, ADC_BASE);
    //GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN7 | GPIO_PIN6 | GPIO_PIN5);
    //SendDataEUSCI_UART(EUSCI_A1_BASE, &IR_main, 2);
    //SendDataEUSCI_UART(EUSCI_A1_BASE, &IR_DC, 2);
    //SendDataEUSCI_UART(EUSCI_A1_BASE, str, 2);



}

// RED LED ON ISR
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER2_B0_VECTOR
__interrupt void TIMER2_CCR0_RED_LED_ON_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER2_B0_VECTOR))) TIMER2_CCR0_RED_LED_ON_ISR (void)
#else
#error Compiler not supported!
#endif
{

    Timer_B_clearCaptureCompareInterrupt(TB2_BASE, TIMER_B_CAPTURECOMPARE_REGISTER_0);

    int16_t Red_main = ReadADC(&photodiode_reading_main, ADC_BASE);
    int16_t Red_DC   = ReadADC(&photodiode_reading_dc_offset, ADC_BASE);
    //GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN7 | GPIO_PIN6 | GPIO_PIN5);

    //SendDataEUSCI_UART(EUSCI_A1_BASE, &Red_main, 2);
    //SendDataEUSCI_UART(EUSCI_A1_BASE, &Red_DC, 2);

}

// RED LED OFF ISR
// Base line measurement
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER2_B1_VECTOR
__interrupt void TIMER2_CCR1_RED_LED_OFF_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER2_B1_VECTOR))) TIMER2_CCR1_RED_LED_OFF_ISR (void)
#else
#error Compiler not supported!
#endif
{

    Timer_B_clearCaptureCompareInterrupt(TB2_BASE, TIMER_B_CAPTURECOMPARE_REGISTER_1);

    int16_t Off_main = ReadADC(&photodiode_reading_main, ADC_BASE);
    int16_t Off_DC   = ReadADC(&photodiode_reading_dc_offset, ADC_BASE);
    //GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN7 | GPIO_PIN6 | GPIO_PIN5);
    //SendDataEUSCI_UART(EUSCI_A1_BASE, &Off_main, 2);
    //SendDataEUSCI_UART(EUSCI_A1_BASE, &Off_DC, 2);

}
