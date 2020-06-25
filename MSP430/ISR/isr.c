/*
 * ISR.c
 *
 *  Created on: Jun 22, 2020
 *      Author: andre
 */

#include "driverlib.h"

// IR LED ON ISR
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_B0_VECTOR
__interrupt void TIMER1_CCR0_IR_LED_ON_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_B0_VECTOR))) TIMER1_CCR0_IR_LED_ON_ISR (void)
#else
#error Compiler not supported!
#endif
{

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

}

// RED LED OFF ISR
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER2_B1_VECTOR
__interrupt void TIMER2_CCR1_RED_LED_OFF_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER2_B1_VECTOR))) TIMER2_CCR1_RED_LED_OFF_ISR (void)
#else
#error Compiler not supported!
#endif
{

}
