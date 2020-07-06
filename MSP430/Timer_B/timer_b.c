/*
 * timer_b.c
 *
 * timer_b.c contains implementation to initialize Timer_B module and utilize it
 *
 *  Created on: May 16, 2020
 *      Author: Andrew Ruf
 */

#include "timer_b.h"


void ConfigureCCModes(const Timer_B_CC_Config * cc_configs, uint8_t num_configs)
{
    unsigned int i;
    for(i = 0; i < num_configs; i++)
    {
        if(cc_configs[i].modeSelect == CAPTURE){
            Timer_B_initCaptureMode(cc_configs[i].baseAddress, &cc_configs[i].Timer_B_CC_config_param.cap_param);
        }
        else
        {
            Timer_B_initCompareMode(cc_configs[i].baseAddress, &cc_configs[i].Timer_B_CC_config_param.comp_param);
        }
    }
}

void ConfigureTimerB(const Timer_B_Config * config, uint16_t baseAddress)
{

    switch(config->mode)
    {
        case STOP:
            Timer_B_stop(baseAddress);
            break;
        case UP:
            Timer_B_initUpMode(baseAddress, &config->Timer_B_config_param.up_param);
            break;
        case UP_DOWN:
            Timer_B_initUpDownMode(baseAddress, &config->Timer_B_config_param.up_down_param);
            break;
        case CONTINUOUS:
            Timer_B_initContinuousMode(baseAddress, &config->Timer_B_config_param.cont_param);
            break;
    }


}


void StartTimerB(const Timer_B_Config * config, uint16_t baseAddress)
{
    switch(config->mode)
    {
    case UP:
        Timer_B_startCounter(baseAddress, TIMER_B_UP_MODE);
        break;
    case UP_DOWN:
        Timer_B_startCounter(baseAddress, TIMER_B_UPDOWN_MODE);
        break;
    case CONTINUOUS:
        Timer_B_startCounter(baseAddress, TIMER_B_CONTINUOUS_MODE);
        break;
    default:
        Timer_B_stop(baseAddress);
    }

}
