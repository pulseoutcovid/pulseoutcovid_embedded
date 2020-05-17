/*
 * clock.c
 *
 * clock.c contains implementation to set the desired core clock using the MSP430Ware drivers
 *
 *  Created on: May 14, 2020
 *      Author: Andrew Ruf
 *
 *
 */

//Include standard library headers
#include <stdbool.h>


//Include MSP430Ware Driver Header
#include "driverlib.h"

//Include header file for functions to implement
#include "clock.h"

CS_initFLLParam fllparam;

/************************************************************
 *  Function: ConfigureClockTree
 *
 *
 *
 *
 *
 *
 *
 ***********************************************************/
bool ConfigureClockTree(ClockTree * tree)
{
    bool retVal = false;
    CS_initClockSignal(CS_FLLREF, tree->Dco.clocksource, tree->Dco.FLLdivider);
    CS_initClockSignal(CS_ACLK, tree->Aclk.clocksource, tree->Aclk.divider);

    // IF DCO is used to generate MCLK frequency, DCO must be
    // initialized to correct settings
    if(tree->Mclk.clocksource == CS_DCOCLKDIV_SELECT){
        if(tree->Dco.outputfrequency == DCO_24MHZ){
            retVal = CS_initFLLSettle(24000, tree->Dco.reference_ratio);
        }
        else if(tree->Dco.outputfrequency == DCO_20MHZ){
            retVal = CS_initFLLCalculateTrim(20000, tree->Dco.reference_ratio, &fllparam);
        }
        else if(tree->Dco.outputfrequency == DCO_16MHZ){
            retVal = CS_initFLLCalculateTrim(16000, tree->Dco.reference_ratio, &fllparam);
        }
        else if(tree->Dco.outputfrequency == DCO_12MHZ){
            retVal = CS_initFLLCalculateTrim(12000, tree->Dco.reference_ratio, &fllparam);
        }
        else if(tree->Dco.outputfrequency == DCO_8MHZ){
            retVal = CS_initFLLCalculateTrim(8000, tree->Dco.reference_ratio, &fllparam);
        }
        else if(tree->Dco.outputfrequency == DCO_4MHZ){
            retVal = CS_initFLLCalculateTrim(4000, tree->Dco.reference_ratio, &fllparam);
        }
        else if(tree->Dco.outputfrequency == DCO_2MHZ){
            retVal = CS_initFLLCalculateTrim(2000, tree->Dco.reference_ratio, &fllparam);
        }
        else if(tree->Dco.outputfrequency == DCO_1MHZ){
            retVal = CS_initFLLCalculateTrim(1000, tree->Dco.reference_ratio, &fllparam);
        }
        // If DCO initialization fails return immediately
        if(retVal == false){
            return false;
        }
    }

    CS_clearAllOscFlagsWithTimeout(1000);

    // Initialize MCLK
    CS_initClockSignal(CS_MCLK, tree->Mclk.clocksource, tree->Mclk.divider);

    //Initialize SMCLK if required
    if(tree->SMclk.enable){
        CS_initClockSignal(CS_SMCLK, tree->Mclk.clocksource, tree->SMclk.divider);
        CS_turnOnSMCLK();

    }

    return true;

}
