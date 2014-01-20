/*
 * MSP_SPI.h
 *
 *  Created on: Oct 11, 2013
 *      Author: C14Angelito.Aragon
 */

#ifndef MSP_SPI_H_
#define MSP_SPI_H_

/*****************************************************************
**Author: Bryan Aragon
**Description:Default Setup for SPI Use
**Inputs:None
**Outputs:Setup for PWM
**Returns:None
**Started: 11 Oct 13
**Finished:
*****************************************************************/
void spi_init();

/*****************************************************************
**Author: Bryan Aragon
**Description:Sends a single byte
**Inputs:None
**Outputs:None
**Returns: SPI Data
**Started: 11 Oct 13
**Finished:
*****************************************************************/
unsigned char sendByte(int byteToSend);

unsigned char send2Bytes(int bytesToSend);


/**
**Author: Bryan Aragon
**Description:Sends an X number of bytes
**
**Inputs: start- pointer to first item in dataToSend array
**Inputs: length- length of dataToSend array
**Inputs: isXbeeAddress- 1 if dataToSend is a 64-bit Xbee address,0 if data
**
**Outputs:None
**Returns: 1 if successful, 0 if not
**Started: 4 Dec 13
**Finished:
 */
unsigned char sendXBytes(long long *start, char length, char isXbeeAddress);

unsigned char readByte();

void set_SS_lo();
void set_SS_hi();


#endif /* MSP_SPI_H_ */
