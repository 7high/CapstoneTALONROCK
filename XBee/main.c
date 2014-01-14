#include <string.h>
#include <msp430.h> 
#include "MSP_SPI.h"
#include "Xbee.h"


/*
 * main.c
 */
int main(void) {


	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	spi_init();

	long long xbeeAddr=0x0013A20040A18EF1;
	long long *pAddress=&xbeeAddr;

	while(1){
		//sendMessage(pAddress,"hello");

		sendBroadcastMessage("hello");

		/*
		long long xbeeAddr2=0x555555559999999;
		long long *pAddress2=&xbeeAddr2;

		sendBroadcastMessage("I am Bryan");
		*/
	}

	//while(1);
}


