/*
 * Xbee.h
 *
 *  Created on: Nov 19, 2013
 *      Author: C14Angelito.Aragon
 */
#include <string.h>
#ifndef XBEE_H_
#define XBEE_H_

/**
 *Sends a message through Xbee API to a particular address
 *Address: XBee address to send data to
 *txData: data to send to desired XBee
 */
void sendMessage(long long *address,char txData[]);

/**
 *Sends a broadcast message through Xbee API.
 *
 *How to call this method
 *Example:
 *	long long xbeeAddr=0x1234567890ABCDEF;
	long long *pAddress=&xbeeAddr;
	sendMessage(pAddress,"hello");
 */
void sendBroadcastMessage(char txData[]);

/**
 * Extracts the message from a Xbee RX data
 *
 * Returns:
 * Pointer to the beginning of the RX data
 */
unsigned char receiveByte();

/**
 * Calculates checksum.
 */
char getChecksum(char frameType, char frameID, long long *address,
		long reservedBytes, char broadcastRad, char transmitOpt, char *data,unsigned int dataLength);



#endif /* XBEE_H_ */
