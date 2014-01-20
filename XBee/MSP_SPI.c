/*
 * MSP_SPI.c
 *
 *  Created on: Oct 11, 2013
 *      Author: C14Angelito.Aragon
 */

#include "MSP_SPI.h"
#include <msp430.h>
#include <string.h>

#define DATA 0x00
#define XBEE_ADDR 0x01
#define DUMMY_CHAR 'V'

void spi_init(){
	UCB0CTL1 |= UCSWRST;

	UCB0CTL0 |= UCMSB|UCMST|UCSYNC; //didn't set UCCKPL

	UCB0CTL1 |= UCSSEL1;

	P1SEL |= BIT5|BIT6|BIT7;        //Clk(P1.5), SOMI(P1.6), SIMO(P1.7)
	P1SEL2 |= BIT5|BIT6|BIT7;

	P2DIR |= BIT1;                //GPIO for SS (P2.1)
	P2DIR &= ~BIT2;				//Set P2.2 for input for SPI_ATTN(Low)

	UCB0CTL1 &= ~UCSWRST;
}

unsigned char readByte(){

	unsigned char readByte;

    set_SS_lo();
    readByte = UCB0RXBUF;//Read contents of receive buffer
    UCB0TXBUF = DUMMY_CHAR; //dummy send

    while(UCB0RXIFG==0);// wait until you've received a byte
	readByte = UCB0RXBUF;//Read contents of receive buffer

    set_SS_hi();

    //return readByte;
    return UCB0RXBUF;
}

unsigned char sendByte(int byteToSend){

    set_SS_lo();

    //Put byte to send in transmission buffer/MOSI
    UCB0TXBUF = byteToSend;

    while(UCB0RXIFG==0);// wait until you've received a byte
	//Set SS back to high to stop talking to Xbee
    set_SS_hi();

    /*
    if(rxData==0x7E){ //if rxData is the delimiter 0x7E
    	while(1){}//hold here
    }
    */

    return UCB0RXBUF;
}

unsigned char send2Bytes(int bytesToSend){
	unsigned int upperByte;
	unsigned int lowerByte;

	upperByte=bytesToSend & 0xFF00;
	upperByte=upperByte >> 8;
	lowerByte=bytesToSend & 0x00FF;

	sendByte(upperByte);
	sendByte(lowerByte);

	return 1;
}

/**
 * Updated: 6 Jan 14
 * Currently appears to work. Can accept any variable-length string and send it.
 */
unsigned char sendXBytes(long long* start, char length, char isXbeeAddress){
	unsigned char i=0; //counter for current place in address
	char* pStdCurrentByte=(char*)start; //MSP puts last byte ahead of the rest
	char* pXbeeCurrentByte=(char*)start+length-1; //MSP puts the first byte last

	unsigned char byteToSend;

	while(i<length){ //while there is more to send


		if(isXbeeAddress==XBEE_ADDR){ //if XBee address, then the first byteToSend is higher in memory
			byteToSend=*pXbeeCurrentByte;
		}else if(isXbeeAddress==DATA) {
			byteToSend=*pStdCurrentByte; //else, the first byteToSend is lower in memory
		}

		sendByte(byteToSend);

		if(isXbeeAddress==XBEE_ADDR){
			pXbeeCurrentByte-=0x01; //decrement 1 to get next byte
		}else if(isXbeeAddress==DATA) {
			pStdCurrentByte+=0x0001; //increment 1 to get next byte
		}

		i++;
	}
	return 1;
}

void set_SS_lo(){
	P2OUT &= ~BIT1;
}

void set_SS_hi(){
	P2OUT |= BIT1;
}
