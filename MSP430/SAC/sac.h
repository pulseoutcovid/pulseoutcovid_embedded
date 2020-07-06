/*
 * sac.h
 *
 *  Created on: Jun 22, 2020
 *      Author: Andrew Ruf
 */

#ifndef MSP430_SAC_SAC_H_
#define MSP430_SAC_SAC_H_

enum SacMode {
    OA      = 1,
    PGA     = 2,
    DAC     = 3
};

typedef struct {
    enum SacMode sacMode;

    uint16_t oaPowerMode;
    uint16_t oaPosInput;
    uint16_t oaNegInput;

    uint16_t pgaGain;
    uint16_t pgaGainMode;

    uint16_t dacRefVoltage;
    uint16_t dacLoad;
    uint16_t dacInitData;
}SAC;


void ConfigureSAC(const SAC * sac_config, uint16_t baseAddress);

#endif /* MSP430_SAC_SAC_H_ */
