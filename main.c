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
#include "driverlib.h"
#include "pulseoutcovid_defines.h"

#include "Board.h"

uint32_t clockValue = 0;

void main (void)
{
    // Stop Watchdog timer
    WDT_A_hold(WDT_A_BASE);

    //DEBUG PURPOSES ONLY
    //Will Be removed

    //Set LED2 to output direction
    GPIO_setAsOutputPin(
        GPIO_PORT_LED2,
        GPIO_PIN_LED2
        );

    //ACLK set out to pins
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_ACLK,
        GPIO_PIN_ACLK,
        GPIO_FUNCTION_ACLK
        );
    //SMCLK set out to pins
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_SMCLK,
        GPIO_PIN_SMCLK,
        GPIO_FUNCTION_SMCLK
        );
    //MCLK set out to pins
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_MCLK,
        GPIO_PIN_MCLK,
        GPIO_FUNCTION_MCLK
        );


    /*
     * Disable the GPIO power-on default high-impedance mode to activate
     * previously configured port settings
     */
    PMM_unlockLPM5();

    //Set DCO FLL Reference = REFO (internal 32768Hz clock)
    CS_initClockSignal(CS_FLLREF, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    //Set ACLK = REFO (internal 32768Hz clock)
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    //Create struct variable to store proper software trim values
    CS_initFLLParam param = {0};

    //Calculate Desired trim values based on desired frequency (24000 kHz)
    //Set Ratio/Desired MCLK Frequency, initialize DCO, save trim values
    if(!CS_initFLLCalculateTrim(CS_MCLK_DESIRED_FREQUENCY_IN_KHZ, CS_MCLK_FLLREF_RATIO, &param)){
        //Error setting MCLK (core clock) to 24MHz
    }

    CS_clearAllOscFlagsWithTimeout(1000);
    //Enable oscillator fault interrupt
    SFR_enableInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);

    // Enable global interrupt
    __bis_SR_register(GIE);

    //Verify if the Clock settings are as expected
    clockValue = CS_getMCLK();

    while (1)
    {
        //Toggle LED2
        GPIO_toggleOutputOnPin(
            GPIO_PORT_LED2,
            GPIO_PIN_LED2
            );

        //Delay
        __delay_cycles(24000000);
    }

}
