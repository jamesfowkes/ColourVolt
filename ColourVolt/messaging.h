#ifndef _CV_MESSAGING_H_
#define _CV_MESSAGING_H_

/*
	messaging.h
*/

void Messaging_Begin(int baud, int eepromAddress);
void Messaging_HandleSerialComms(void);
bool Messaging_MessageIsEqualTo(char const * str);
void Messaging_SendVoltage(unsigned int mv);
void Messaging_SendMessage(char const * message);
void Messaging_SendVoltageWithPrefix(char const * message, unsigned int mv);
#endif
