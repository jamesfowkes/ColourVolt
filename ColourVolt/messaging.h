#ifndef _CV_MESSAGING_H_
#define _CV_MESSAGING_H_

/*
	messaging.h
*/

void messagingBegin(int baud, int eepromAddress);
void handleSerialComms(void);
bool messageEquals(char const * str);
void sendVoltage(unsigned int mv);
void sendMessage(char const * message);
void sendVoltageWithPrefix(char const * message, unsigned int mv);
#endif