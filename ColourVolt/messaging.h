#ifndef _CV_MESSAGING_H_
#define _CV_MESSAGING_H_

/**
 * This module handles LLAP style messaging for low memory microcontrollers.
 * The module uses the Arduino SoftwareSerial library.
 * LLAP support is not complete. Currently the following commands/messages are supported:
 *  - CHDEVID
 *  - STARTED

 * The module requires two bytes of EEPROM memory to store the device ID
 
 * The module should be initialised by calling Messaging_Begin:
    
	Messaging_Begin(BAUD_RATE, DEVICE_ID_ADDRESS);
	
 * where:
 * BAUD_RATE is the baud rate for the software serial
 * DEVICE_ID_ADDRESS is the EEPROM address to read/write the device ID
 
 * When this is called, the module will:
 *  - Initialise a software serial object at the requested baud rate. Pin 9 is used for RX, pin 10 for TX
 *  - (Future library versions may have configurable RX/TX pin mapping)
 *  - Read the device ID from the supplied EEPROM address
 *  - If the device ID is invalid, reset the device id to '--' (the LLAP default)
 *  - Send a standard LLAP STARTED message (e.g. 'a--STARTED' for the default ID)

 * The application must call Messaging_HandleSerialComms regularly in order to process incoming messages.
 * If the application is required to sleep for long periods of time, it is recommended to test the messaging module carefully to ensure receipt of messages.
 
 * When a new serial character is received:
 *  - The module buffers these characters until a newline or carriage return is found.
 * When a newline or carriage return is found:
 *  - The module attempts to process the buffered characters as an LLAP message.
 *  - The message is checked for validity (starts with 'a') and for matching device ID.
 *  - If the message is valid, the content is checked.
 *  - Some known LLAP messages (for example CHDEVID) are handled by the module.
 *  - Other messages are passed to the application for handling.
 *  - The application must have a APP_HandleReceivedMsg(void) function to handle the message.
 *  - The module provides an Messaging_MessageIsEqualTo function to query message content

 * For example, this function looks for messages with content "ON" or "OFF":
 
    void APP_HandleReceivedMsg(const char * message)
    {
        if Messaging_MessageIsEqualTo("ON")
        {
            turnSomethingOn();
        }
        else if Messaging_MessageIsEqualTo("OFF")
        {
            turnSomethingOff();
        }
    }
 
 * Note that the function is passed a pointer to the message so it may be read, but not modified.
 
 * To send messages, the module provides the following functions:
 * - Messaging_SendMessage(char const * message)
 * - Messaging_SendVoltage(unsigned int mv)
 * - Messaging_SendVoltageWithPrefix(char const * message, unsigned int mv)

 * All the message functions will:
 * - automatically prefix the message with the correct LLAP header ('aXX', where XX is the device ID)
 * - automatically fill any remaining message bytes with the '-' character
 
 * Messaging_SendMessage simply sends the message provided, up to 10 chars. Any chars beyond 10 are discarded. For example:

    Messaging_SendMessage("HELLO!");
    
 * will send the message 'aXXHELLO!----' where XX is the device ID
 
 * Messaging_SendVoltage will assume the provided number is a voltage in millivolts and format it as as voltage to 2.dp. For example:
 
    Messaging_SendVoltage(15537);
    
 * will send the message 'aXX15.54V----' where XX is the device ID. Note that the number is correctly rounded.
 
 * Messaging_SendVoltageWithPrefix will perform the same as Messaging_SendVoltage, but will add an additional prefix before the voltage. For example:
 
    Messaging_SendVoltageWithPrefix("DC", 5937);
 
 * will send the message 'aXXDC5.94V---' where XX is the device ID. This can make it easier to distinguish between voltage messages.
 
 * Note that in future versions of the library the voltage-to-string conversion may be moved to another library.
 * This should not affect use of the messaging library from an application perspective.
*/

void Messaging_Begin(int baud, int eepromAddress);
void Messaging_HandleSerialComms(void);
bool Messaging_MessageIsEqualTo(char const * str);
void Messaging_SendVoltage(unsigned int mv);
void Messaging_SendMessage(char const * message);
void Messaging_SendVoltageWithPrefix(char const * message, unsigned int mv);
#endif
