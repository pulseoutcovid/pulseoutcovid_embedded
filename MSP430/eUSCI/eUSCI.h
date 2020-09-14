/*
 * eUSCI.h
 *
 *  Created on: Jul 25, 2020
 *      Author: andre
 */

#ifndef MSP430_EUSCI_EUSCI_H_
#define MSP430_EUSCI_EUSCI_H_


enum eUSCIMODE
{
    SPI_MASTER_A        = 0,
    SPI_MASTER_B        = 1,
    SPI_SLAVE_A         = 2,
    SPI_SLAVE_B         = 3,
    UART                = 4,
    I2C_MASTER          = 5,
    I2C_SLAVE           = 6
};

typedef union
{
  //SPI MASTER
  EUSCI_A_SPI_initMasterParam eUSCI_A_SPI_master_config;
  EUSCI_B_SPI_initMasterParam eUSCI_B_SPI_master_config;

  //SPI SLAVE
  EUSCI_A_SPI_initSlaveParam eUSCI_A_SPI_slave_config;
  EUSCI_B_SPI_initSlaveParam eUSCI_B_SPI_slave_config;

  //UART
  EUSCI_A_UART_initParam eUSCI_A_UART_config;

  //I2C Master
  EUSCI_B_I2C_initMasterParam eUSCI_B_I2C_master_config;

  //I2C Slave
  EUSCI_B_I2C_initSlaveParam  eUSCI_B_I2C_slave_config;


} eUSCI_mode_config;

typedef struct
{
    enum eUSCIMODE eUSCImode;
    eUSCI_mode_config mode_config;

    uint8_t interrupt_mask;


} EUSCI_config;

bool ConfigureEUSCI(const EUSCI_config * eUSCI_config, uint16_t baseAddress);
void SendDataEUSCI_UART(uint16_t baseAddress, uint8_t * data, uint16_t dataLength);


#endif /* MSP430_EUSCI_EUSCI_H_ */
