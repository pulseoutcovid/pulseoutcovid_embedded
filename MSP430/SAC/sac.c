/*
 * sac.c
 *
 *  Created on: Jun 22, 2020
 *      Author: Andrew Ruf
 */

//Include standard library headers
#include <stdbool.h>


//Include MSP430Ware Driver Header
#include "driverlib.h"

//Include header file for functions to implement
#include "sac.h"


inline void ConfigureDAC_PGA(const SAC * sac_config, uint16_t baseAddress)
{
    //DAC configuration
    SAC_DAC_selectRefVoltage(baseAddress, sac_config->dacRefVoltage);
    SAC_DAC_selectLoad(baseAddress, sac_config->dacLoad);
    SAC_DAC_setData(baseAddress, sac_config->dacInitData);
    SAC_DAC_enable(baseAddress);

    //Set OA to be a buffer for DAC output
    SAC_OA_init(baseAddress, sac_config->oaPosInput, sac_config->oaNegInput);
    SAC_OA_selectPowerMode(baseAddress, sac_config->oaPowerMode);

    SAC_PGA_setGain(baseAddress, sac_config->pgaGain);
    SAC_PGA_setMode(baseAddress, sac_config->pgaGainMode);

    //Enable
    SAC_OA_enable(baseAddress);
    SAC_enable(baseAddress);
}

inline void ConfigureOA(const SAC * sac_config, uint16_t baseAddress)
{
    //DAC configuration
    SAC_DAC_selectRefVoltage(baseAddress, sac_config->dacRefVoltage);
    SAC_DAC_selectLoad(baseAddress, sac_config->dacLoad);
    SAC_DAC_setData(baseAddress, sac_config->dacInitData);
    SAC_DAC_enable(baseAddress);

    //OA Initialization
    SAC_OA_init(baseAddress, sac_config->oaPosInput, sac_config->oaNegInput);
    SAC_OA_selectPowerMode(baseAddress, sac_config->oaPowerMode);
    //Enable
    SAC_OA_enable(baseAddress);
    SAC_enable(baseAddress);
}


void ConfigureSAC(const SAC * sac_config, uint16_t baseAddress)
{
    switch(sac_config->sacMode)
    {
        case OA:
            ConfigureOA(sac_config,baseAddress);
        break;

        case PGA:
        case DAC:
            ConfigureDAC_PGA(sac_config, baseAddress);
        break;
    }
}
