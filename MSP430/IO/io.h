/*
 * io.h
 *
 * io.h contains implementation to initialize pins and set pin behavior
 *
 *  Created on: May 16, 2020
 *      Author: Andrew Ruf
 */

#ifndef MSP430_IO_IO_H_
#define MSP430_IO_IO_H_


enum PinDirection {
    INPUT   = 0,
    OUTPUT  = 1,
    EITHER  = 2,
};


typedef struct Pin{
    uint8_t port;
    uint8_t pin;
    enum PinDirection direction;
    uint8_t mode;
    bool enable;
} Pin;


void ConfigurePins(const Pin * pins, uint8_t number_pins);


#endif /* MSP430_IO_IO_H_ */
