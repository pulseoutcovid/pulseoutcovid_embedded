/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

//C Std Includes
#include <stdbool.h>
#include <string.h>

//Include MSP430Ware Driver Header
#include "driverlib.h"

//Include peripheral headers
#include "MSP430/Clock/clock.h"
#include "MSP430/Timer_B/timer_b.h"
#include "MSP430/SAC/sac.h"
#include "MSP430/eUSCI/eUSCI.h"

//PulseOutCovid Global Defines
#include "pulseoutcovid_config.h"

#include "Board.h"

uint32_t clockValue = 0;

void main (void)
{
    // Stop Watchdog timer
    WDT_A_hold(WDT_A_BASE);

    /*
     * Disable the GPIO power-on default high-impedance mode to activate
     * previously configured port settings
     */
    PMM_unlockLPM5();

    // Configure Clock Tree
    ConfigureClockTree(&tree);
    //Verify if the Clock settings are as expected
    clockValue = CS_getMCLK();

    //Configure UART
    bool uart_status = ConfigureEUSCI(&EUSCI_A1_config, EUSCI_A1_BASE);
    if(!uart_status)
    {
        //Error
        while(1);
    }

    //Configure IO
    ConfigurePins(pins, NUM_CONFIG_PINS);

    char ok_status[] = "UART Ready!\n";
    SendDataEUSCI_UART(EUSCI_A1_BASE, &ok_status, 11);


#if !DEBUG
    //Configure SACs
    //Configure SAC0
    //IR LED Current Control DAC
    ConfigureSAC(&sac_LED_config, SAC0_BASE);
    //Configure SAC2
    //Red LED Current Control DAC
    ConfigureSAC(&sac_LED_config, SAC2_BASE);

    //Configure SAC1
    //TIA
    ConfigureSAC(&sac_1_config, SAC1_BASE);

    //Configure SAC3
    //Gain Stage Amplifier
    ConfigureSAC(&sac_3_config, SAC3_BASE);

    //Configure TimerB
    ConfigureTimerB(&timer_b_config, TB1_BASE);
    ConfigureTimerB(&timer_b_config, TB2_BASE);
    Timer_B_enableCaptureCompareInterrupt(TB2_BASE, TIMER_B_CAPTURECOMPARE_REGISTER_0);

    //Setup CC registers
    ConfigureCCModes(CC_configs, NUM_CC_CONFIGS);

    //Configure ADC
    ConfigureADC(&adc_config, ADC_BASE);
#endif

    StartTimerB(&timer_b_config, TB1_BASE);
    StartTimerB(&timer_b_config, TB2_BASE);

    //Enable oscillator fault interrupt
    SFR_enableInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);

    GPIO_setOutputLowOnPin(RED_IND_LED_PORT, GREEN_IND_LED_PIN | RED_IND_LED_PIN | YELLOW_IND_LED_PIN);
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN0);

    // Enable global interrupt
    __bis_SR_register(GIE);
    while (1)
    {

#if DEBUG
        //Delay
        __delay_cycles(120000);
        GPIO_toggleOutputOnPin(RED_IND_LED_PORT, GREEN_IND_LED_PIN | RED_IND_LED_PIN | YELLOW_IND_LED_PIN);
        GPIO_toggleOutputOnPin(GPIO_PORT_P5, GPIO_PIN0);
#endif
    }

}
