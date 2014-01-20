#include <string.h>
#include <msp430.h> 
#include "MSP_SPI.h"
#include "Xbee.h"

#define RX_ARRAY_SIZE 50


/*
 * main.c
 */
int main(void) {


	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	spi_init();

	/*//TX Test code
	long long xbeeAddr=0x0013A20040A18EF1;
	long long *pAddress=&xbeeAddr;

	while(1){
		//sendMessage(pAddress,"hello");
		sendBroadcastMessage("hello");
	}
	*/



	//RX Test code
	unsigned char rxMessage[RX_ARRAY_SIZE]="55555555555555555555555555555555555555555555555555";
	unsigned char i=0;

	//Set LED to output
	P1DIR |= 0x41;

	while(1){
		// Continuously run Xbee.receiveMessage method
		//rxByte=receiveByte();

		while(P2IN&0x04){}//Wait for SPI_ATTN to go low

		rxMessage[i]=readByte();

		if(i<RX_ARRAY_SIZE){
			i++;
		}else{
			i=0;
		}



	}

}


/*//For data validation. Use later
if(readByte()== 0x7E){
	isValid=1;
}
*/
