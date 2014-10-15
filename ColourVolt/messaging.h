#ifndef _CV_MESSAGING_H_
#define _CV_MESSAGING_H_

/*
	messaging.h
*/

void messagingBegin(int baud, int eepromAddress);
void handleSerialComms(void);
bool messageEquals(char * str);
void sendVoltage(unsigned int mv);
void sendMessage(char * message);

#endif
