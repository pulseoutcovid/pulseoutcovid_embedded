/*
 * clock.h
 *
 *  Created on: May 14, 2020
 *      Author: Andrew Ruf
 */

#ifndef MSP430_CLOCK_CLOCK_H_
#define MSP430_CLOCK_CLOCK_H_

#include <stdbool.h>
#include <stdint.h>


enum DcoFrequency{
    DCO_1MHZ    = 1,
    DCO_2MHZ    = 2,
    DCO_4MHZ    = 4,
    DCO_8MHZ    = 8,
    DCO_12MHZ    = 8,
    DCO_16MHZ   = 16,
    DCO_20MHZ   = 20,
    DCO_24MHZ   = 24
};

struct Dco{

    uint8_t clocksource;
    uint16_t FLLdivider;
    enum DcoFrequency outputfrequency;
    uint16_t reference_ratio;
};

struct Aclk{
    uint8_t clocksource;
    uint16_t divider;
};

struct Mclk{
    uint8_t clocksource;
    uint16_t divider;
};

struct SMclk{
    uint16_t divider;
    bool enable;
};


typedef struct ClockTree{
   struct Dco Dco;
   struct Aclk Aclk;
   struct Mclk Mclk;
   struct SMclk SMclk;

} ClockTree;


bool ConfigureClockTree(ClockTree * tree);



#endif /* MSP430_CLOCK_CLOCK_H_ */
