/*

	messsaging.cpp
	
	- Handles LLAP style messaging for ColourVolt
	
*/

/* Arduino Library Includes */
#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

/* Application Includes */
#include "messaging.h"

/* Defines and Typedefs */
#define RX_PIN 9
#define TX_PIN 10

/* Extern Function Prototypes */
extern void handleRxMessage(char * message); // Application message handler

/* Private Function Prototypes */
static uint8_t getPlaceCount(unsigned int value, unsigned int place);
static uint8_t toString(unsigned int val, char * buf);

/* Private Objects and Variables */
static SoftwareSerial s_softSerial(RX_PIN, TX_PIN);
static char s_deviceID[] = "??";

static char s_rxMessage[13];
static uint8_t s_rx = 0;

static char s_txMessage[13];

static int s_eepromAddress = 0;

/* Private Function Definitions */

static bool isValidMessage(void)
{
	// All messages should start with lowercase a
	return s_rxMessage[0] == 'a';
}

static bool deviceIDsMatch(void)
{
	// Both chars of device ID should match
	bool match = true;
	match &= (s_deviceID[0] == s_rxMessage[1]);
	match &= (s_deviceID[1] == s_rxMessage[2]);

	return match;
}

static void initTxMessage(void)
{
	s_txMessage[0] = 'a';
	s_txMessage[1] = s_deviceID[0];
	s_txMessage[2] = s_deviceID[1];


	uint8_t i;
	for (i = 3; i < 13; i++)
	{
		s_txMessage[i] = '-';
	}
}

static uint8_t toString(unsigned int val, char * buf)
{
	unsigned int  placevalue = 0;
	uint8_t digitcount = 0;
	bool foundSignificantDigit = false;
	uint8_t bytesWritten = 0;

	for (placevalue = 1000; placevalue > 1; placevalue /= 10)
	{
		digitcount = getPlaceCount(val, placevalue);
		if (digitcount || foundSignificantDigit)
		{
			foundSignificantDigit = true;
			*buf++ = (char)(digitcount + '0');
			val -= (digitcount * placevalue);
			bytesWritten++;
		}
	}

	digitcount = val;
	*buf++ = (char)(digitcount + '0');
	bytesWritten++;

	return bytesWritten;
}

// getPlaceCount
// - Get the magnitude at the specified digit in a number
static uint8_t getPlaceCount(unsigned int value, unsigned int place)
{
	if (place > 1 && value > 0)
	{
		return (uint8_t)(value / place);
	}
	else
	{
		return value - (10 * (value / 10));
	}
}

static bool validIDChar(char id)
{
	bool valid = true;
	valid &= (id <= 'Z');
	valid &= (id >= 'A');
	valid |= (id == '-');
	valid |= (id == '#');
	valid |= (id == '@');
	valid |= (id == '?');
	valid |= (id == '\\');
	valid |= (id == '*');

	return valid;
}

static bool setDeviceID(char a, char b)
{
	bool valid = validIDChar(a) && validIDChar(b);
	if (valid)
	{
		s_deviceID[0] = a;
		s_deviceID[1] = b;
		EEPROM.write(s_eepromAddress, a);
		EEPROM.write(s_eepromAddress+1, b);
	}
	return valid;
}

static uint8_t copyToTxMessage(char const * message, uint8_t idx)
{
	uint8_t count = 0;
	
	// Copy message into tx buffer
	if(message != NULL)
	{
		idx += 3; // Translate message index to index of LLAP buffer
		while (message[count] != '\0' && count < 9)
		{
			s_txMessage[count+idx] = message[count];
			count++;
		}
	}
	
	return count;
}

static void voltageToTxMessage(unsigned int mv, uint8_t idx)
{
	if (idx > 4) { return; } // No space for voltage in buffer
	
	mv = (mv + 5) / 10; // Only send two decimal places (with rounding, so 12345/10 becomes 1235)

	// Convert numeric into message starting at 4th char
	char * voltage = &s_txMessage[3+idx];
	uint8_t length = toString(mv, voltage);

	if (length == 1)
	{
		// Pad with leading zeros so that at 2 chars are written, e.g "1" becomes "01"
		voltage[length] = voltage[length-1];
		voltage[length-1] = '0'; 
		length++;
	}

	if (length == 2)
	{
		// Pad with leading zero so that at 3 chars are written, e.g "01" becomes "001"
		voltage[length] = voltage[length-1];
		voltage[length-1] = voltage[length-2];
		voltage[length-2] = '0'; 
		length++;
	}

	// Shift the last two chars to the right
	// Then add decimal point and 'V' symbol
	// e.g. "100" becomes "1.00"

	voltage[length] = voltage[length-1];
	voltage[length-1] = voltage[length-2];
	voltage[length-2] = '.';
	voltage[length + 1] = 'V';	
}

/* Public Function Defintions */

void Messaging_Begin(int baud, int eepromAddress)
{  

	s_softSerial.begin(baud);

	s_eepromAddress = eepromAddress;

	s_deviceID[0] = EEPROM.read(s_eepromAddress);
	s_deviceID[1] = EEPROM.read(s_eepromAddress + 1);

	if (!validIDChar(s_deviceID[0]) || !validIDChar(s_deviceID[1]))
	{
		s_softSerial.print("Invalid ID:");
		s_softSerial.print(s_deviceID[0]);
		s_softSerial.println(s_deviceID[1]);
		(void)setDeviceID('-', '-'); // Default to '--' as ID if EEPROM not valid
	}

	initTxMessage();
	Messaging_SendMessage("STARTED");
}

void Messaging_HandleSerialComms(void)
{
	if (s_softSerial.available())
	{
		// There is a new char ready in the serial buffer
		char newChar = s_softSerial.read();

		if ((newChar != '\n') && (newChar != '\r'))
		{
			// Not the end of a message, store char and exit
			s_rxMessage[s_rx++] = newChar;
		}
		else
		{
			// End of message
			if (isValidMessage() && deviceIDsMatch())
			{
				// Valid LLAP message, for this device
				if (Messaging_IsMessageEqualTo("CHDEVID"))
				{
					// Instruction to change device ID - handle locally
					if (setDeviceID(s_rxMessage[10], s_rxMessage[11]))
					{
						initTxMessage();
						char reply[] = "CHDEVID--";
						reply[7] = s_deviceID[0];
						reply[8] = s_deviceID[1];
						Messaging_SendMessage(reply);
					}
				}
				else
				{
					// Pass message excluding 'aXX' to application
					handleRxMessage(&s_rxMessage[3]);
				}
			}
			s_rx = 0;
		}
	}   
}

bool Messaging_IsMessageEqualTo(char const * str)
{
	int len = strlen(str);
	int i;

	// Look through receive message chars starting at index 3 (after device ID)
	for (i = 0; i < len; ++i)
	{
		// Return false as soon as a char doesn't match
		if (s_rxMessage[3+i] != str[i]) { 
			return false; 
		}
	}

	// If here, must have matched all chars.
	return true;
}

void Messaging_SendVoltage(unsigned int mv)
{
	// Takes voltage in millivolts and sends to serial port (2 d.p.)
	// e.g. 12345 mv gets sent as aXX12.34V where XX is the device ID

	initTxMessage();
	voltageToTxMessage(mv, 0);
	s_softSerial.println(s_txMessage);
}

void Messaging_SendVoltageWithPrefix(char const * message, unsigned int mv)
{
	uint8_t count = 0;

	initTxMessage();
	count = copyToTxMessage(message, 0);
	voltageToTxMessage(mv, count);
	s_softSerial.println(s_txMessage);
}

void Messaging_SendMessage(char const * message)
{
	initTxMessage();
	(void)copyToTxMessage(message, 0);
	s_softSerial.println(s_txMessage);
}
