#include <string.h>
#include <msp430.h> 
#include "MSP_SPI.h"
#include "Xbee.h"

#define RX_ARRAY_SIZE 50

#define THE_BRASS 0x0013A20040A18EF1
#define THE_WIRE 0x0013A20040AE91BA
#define THE_DOT 0x0013A20040AE929C

#define MESS1 "hello"
#define MESS2 "Bryan"
#define MESS3 "Hello I'm Bryan"



/*
 * main.c
 */
int main(void) {


	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	spi_init();

	/*
	//TX Test code
	long long xbeeAddr=THE_BRASS;
	long long *pAddress=&xbeeAddr;

	while(1){
		//sendMessage(pAddress, "hello");
		sendMessage(pAddress, MESS1);
		//sendBroadcastMessage(MESS1);
	}//End TX Test code
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
	}//End RX Test Code





}


/*//For data validation. Use later
if(readByte()== 0x7E){
	isValid=1;
}
*/
