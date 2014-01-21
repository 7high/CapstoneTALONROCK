/*
 * Xbee.c
 *
 *  Created on: Nov 19, 2013
 *      Author: C14Angelito.Aragon
 */
#include <stdio.h>
#include <string.h>
#include "MSP_SPI.h"
#include "Xbee.h"
#include <msp430.h>

#define ARRAY_SIZE 50

#define START_DELIMITER 0x7E
#define TX_REQUEST 0x10

#define TX_FRAME_LENGTH_WO_TXDATA 14

#define NO_FRAME_ID 0x00
#define GET_FRAME_ID 0x01

#define DATA 0x00
#define XBEE_ADDR 0x01

#define XBEE_ADDR_LENGTH 0x08

#define RESERVED_BYTES 0xFFFE

#define MAX_BROADCAST_RAD 0x00

#define USE_TO_PARAM 0x00

/**
 * Updated: 6 Jan 14
 * Code appears finished. Still needs further testing with actual Xbee tranmissions
 */
void sendMessage(long long *address,char txData[]){
	unsigned char checksum=0;

	sendByte(START_DELIMITER);

	unsigned int dataLength=strlen(txData);
	unsigned int messageLength=strlen(txData)+TX_FRAME_LENGTH_WO_TXDATA;

	send2Bytes(messageLength);

	sendByte(TX_REQUEST);
	sendByte(GET_FRAME_ID);

	sendXBytes(address,XBEE_ADDR_LENGTH,XBEE_ADDR);

	send2Bytes(RESERVED_BYTES);
	sendByte(MAX_BROADCAST_RAD);
	sendByte(USE_TO_PARAM);

	sendXBytes((long long *)txData,dataLength,DATA);

	checksum=getChecksum(TX_REQUEST,GET_FRAME_ID,address,RESERVED_BYTES,MAX_BROADCAST_RAD,USE_TO_PARAM,txData,dataLength);

	sendByte(checksum);


}


void sendBroadcastMessage(char txData[]){
	//Set pAddr to Xbee's broadcast address
	long long broadcastAddr=0x000000000000FFFF;
	long long *pAddr=&broadcastAddr;

	sendMessage(pAddr,txData);
}

unsigned char* receiveMessage(){
	unsigned int rxMessageArraySize;
	unsigned char messageArray[ARRAY_SIZE];
	unsigned int messageLength;
	unsigned int upperLengthInt;
	unsigned char i=0;

	while(P2IN&0x04){}//Wait for SPI_ATTN to go low

	/*//Trial code
	while(readByte()!=0x7E){}//Wait for 0x7E

	//Get message length by concatenating the two lengthBytes
	unsigned char upperLength=readByte();
	unsigned char lowerLength=readByte();
	upperLengthInt=upperLength << 8;
	messageLength=upperLengthInt+lowerLength;

 	while(readByte()!=0x90){} //Wait for RX Indicator frame type byte

	rxMessageArraySize=TX_FRAME_LENGTH_WO_TXDATA+messageLength;// Determine length of message

	for(i=0;i<rxMessageArraySize;i++){
		messageArray[i]=readByte();
	}//End trial code
	*/

	for(i=0;i<ARRAY_SIZE;i++){
		messageArray[i]=readByte();
	}

	if(i<ARRAY_SIZE){
		i++;
	}else{
		i=0;
	}
	return messageArray;
	//End working code

}

/**
 * Updated: 6 Jan 14
 * Tested method successfully: 1/1
 */
char getChecksum(char frameType, char frameID, long long *address,
		long reservedBytes, char broadcastRad, char transmitOpt, char *data, unsigned int dataLength){

	volatile char checksum=0;
	int i=0;
	int j=0;
	char* pAddr=(char*)address;
	char* pData=data;

	checksum=frameType;
	checksum+=frameID;

	for(i=0;i<XBEE_ADDR_LENGTH;i++){
		checksum+=*pAddr;
		pAddr+=0x01;
	}

	long reservedBytes1=reservedBytes & 0xFF00;
	reservedBytes1=reservedBytes1>>8; //shifts 0xFFxx to 0x00FF
	long reservedBytes2=reservedBytes & 0x00FF;

	checksum+=reservedBytes1;
	checksum+=reservedBytes2;

	checksum+=broadcastRad;
	checksum+=transmitOpt;

	for(j=0;j<dataLength;j++){
		checksum+=*pData;
		pData+=0x01;
	}

	checksum=0xFF-checksum;

	return checksum;
}

