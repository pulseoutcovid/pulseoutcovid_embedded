/*
 * eUSCI.c
 *
 *  Created on: Jul 25, 2020
 *      Author: andre
 */

//Include MSP430Ware Driver Header
#include "driverlib.h"

//Include header file for functions to implement
#include "eUSCI.h"


inline bool ConfigureUART(const EUSCI_config * eUSCI_config, uint16_t baseAddress)
{
    bool uart_status = EUSCI_A_UART_init(baseAddress,
                                         &eUSCI_config->mode_config.eUSCI_A_UART_config);
    if(uart_status)
    {
        //Clear Interrupts left over
        EUSCI_A_UART_clearInterrupt(baseAddress, 0xFFFF);
        EUSCI_A_SPI_enableInterrupt(baseAddress, eUSCI_config->interrupt_mask);
        EUSCI_A_SPI_enable(baseAddress);
    }
    return uart_status;
}

bool ConfigureEUSCI(const EUSCI_config * eUSCI_config, uint16_t baseAddress)
{
   bool status;
   switch(eUSCI_config->eUSCImode)
   {
   case SPI_MASTER_A:

       break;

   case UART:
       status = ConfigureUART(eUSCI_config, baseAddress);
       break;
   }

   return status;
}

void SendDataEUSCI_UART(uint16_t baseAddress, uint8_t * data, uint16_t dataLength)
{
    uint16_t x;
    for(x = 0; x < dataLength; x++)
    {
        EUSCI_A_UART_transmitData(baseAddress, data[x]);
    }
    return;
}
