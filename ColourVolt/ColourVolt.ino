/*
  ColourVolt
 
 - Reads power supply voltage and outputs "within range" status via RGB LED
 - Range is set by two potentiometers (for 'ideal' voltage and acceptable range)
 - Serial connection allows calibration and diagnostics
 
 - Target: ATTINY84
 */

/* Arduino Library Includes */
#include <TaskAction.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

/* Application Includes */
#include "calibration.h"

/* Defines */
#define RED_PIN 6
#define GRN_PIN 5
#define BLU_PIN 7

#define VOLTS_PIN A0
#define SETPOINT_PIN A1
#define RANGE_PIN A2

#define RX_PIN 9
#define TX_PIN 10

#define DEVICE_ID_EEPROM_ADDRESS 0x00 // 2 bytes
#define CALIBRATION_EEPROM_ADDRESS 0x02 // 2 bytes

/* Software Tasks */
TaskAction readMainADCTask = TaskAction(readMainADC, 20, INFINITE_TICKS);
TaskAction readRangeADCsTask = TaskAction(readRangeADCs, 100, INFINITE_TICKS);

/* Private Variables */
int voltageReading = 0;
int lowThreshold = 0;
int highThreshold = 0;
int setpointReading = 0;
int rangeReading = 0;

bool newReadingReady = false;

SoftwareSerial softSerial(RX_PIN, TX_PIN);
char deviceID[] = "??";

char rxMessage[13];
char rx = 0;
char txMessage[13];

void setup() {

  pinMode(RED_PIN, OUTPUT);    
  pinMode(GRN_PIN, OUTPUT); 
  pinMode(BLU_PIN, OUTPUT);

  softSerial.begin(4800);
  softSerial.println("ColourVolt");

  deviceID[0] = EEPROM.read(DEVICE_ID_EEPROM_ADDRESS);
  deviceID[1] = EEPROM.read(DEVICE_ID_EEPROM_ADDRESS + 1);

  // Give the calibration module its EEPROM address so it can read stored value
  Calib_setup(CALIBRATION_EEPROM_ADDRESS);

  // Make sure threshold is properly set before the LEDs are updated
  readRangeADCs();
}

void loop() 
{
  if( newReadingReady )
  { 
    // There is a new ADC reading of the power input
    processNewReading();
    newReadingReady = false;
  }

  // Run the tasks
  readMainADCTask.tick();
  readRangeADCsTask.tick();

  handleSerialComms();
}

void processNewReading(void)
{
  if ( Calib_inProgress() )
  {
    // Update the calibration software - this has no effect unless calibration is running
    setLEDs(LOW, LOW, LOW);
    Calib_newValue(voltageReading); 
  }
  else
  {
    // Normal operation - Just set the output LEDs
    updateLEDs();
  } 
}

void updateLEDs(void)
{
  // Sets LED colour based on current reading
  if (voltageReading <= lowThreshold) // Below range
  {
    setLEDs(LOW, HIGH, HIGH); // Red
  }
  else if (voltageReading >= highThreshold) // Above range
  {
    setLEDs(HIGH, HIGH, LOW); // Blue
  }
  else // In range
  {
    setLEDs(HIGH, LOW, HIGH); // Green
  }
}

void setLEDs(int r, int g, int b)
{
  // Control the R,G,B leds. 
  digitalWrite(RED_PIN, r);
  digitalWrite(GRN_PIN, g);
  digitalWrite(BLU_PIN, b);
}

void readMainADC(void)
{
  /* Reads the main ADC and flags that a new reading is ready */
  voltageReading = analogRead(VOLTS_PIN);
  newReadingReady = true;
}

void readRangeADCs(void)
{
  /* Reads the setpoint and range pots. and calculates new hi/lo thresholds */
  int newSetpointReading = analogRead(SETPOINT_PIN);
  int newRangeReading = analogRead(RANGE_PIN);

  if ((setpointReading != newSetpointReading) || (rangeReading != newRangeReading))
  {
    setpointReading = newSetpointReading;
    rangeReading = newRangeReading;
    // lowThreshold might go < 0, highThreshold might go > 1023
    // This doesn't really matter, just means that reading will never go outside of valid range!
    lowThreshold = setpointReading - (rangeReading / 2);
    highThreshold = setpointReading + (rangeReading / 2);
  }
}

void handleSerialComms(void)
{
  if (softSerial.available())
  {
    char newChar = softSerial.read();

    if (newChar != '\n')
    {
      rxMessage[rx++] = newChar;
    }
    else if (newChar == '\n')
    {
      handleRxMessage();
      rx = 0;
    }
  }   
}

void handleRxMessage(void)
{
  if (isValidMessage() && deviceIDsMatch())
  {
    if (messageEquals("CHDEVID"))
    {
      setDeviceID(rxMessage[10], rxMessage[11]);
    }
    else if (messageEquals("V?"))
    {
      unsigned int voltage = Calib_toMilliVolts(voltageReading);
      sendVoltage(voltage);
    }
    else if (messageEquals("HT?"))
    {
      unsigned int voltage = Calib_toMilliVolts(highThreshold);
      sendVoltage(voltage);
    }
    else if (messageEquals("LT?"))
    {
      unsigned int voltage = Calib_toMilliVolts(lowThreshold);
      sendVoltage(voltage);
    }
    else if (messageEquals("CAL"))
    {
      Calib_start();
    }
  }
}

bool messageEquals(char * str)
{
  int len = strlen(str);
  int i;

  // Look through receive message chars starting at index 3 (after device ID)
  for (i = 0; i < len; ++i)
  {
    // Return false as soon as a char doesn't match
    if (rxMessage[3+i] != str[i]) { 
      return false; 
    }
  }

  // If here, must have matched all chars.
  return true;
}

bool isValidMessage(void)
{
  // All messages should start with lowercase a
  return rxMessage[0] == 'a';
}

bool deviceIDsMatch(void)
{
  // Both chars of device ID should match
  bool match = true;
  match &= (deviceID[0] == rxMessage[1]);
  match &= (deviceID[1] == rxMessage[2]);

  return match;
}

void setDeviceID(char a, char b)
{
      deviceID[0] = a;
      deviceID[1] = b;
      EEPROM.write(DEVICE_ID_EEPROM_ADDRESS, a);
      EEPROM.write(DEVICE_ID_EEPROM_ADDRESS+1, b);
}

void sendVoltage(unsigned int mv)
{
  // Takes voltage in millivolts and sends to serial port (2 d.p.)
  // e.g. 12345 mv gets sent as aXX12.34V where XX is the device ID
  
  initTxMessage();
  
  mv = mv / 10; // Only send two decimal places (so 12345 becomes 1234)
  
  // Convert numeric into message starting at 4th char
  char length = 0;//toString(mv, &txMessage[3]) + 3;
  
  // Shift the last two chars to the right
  // Then add decimal point , 'V' symbol and a new null terminator 

  txMessage[length] = txMessage[length-1];
  txMessage[length-1] = txMessage[length-2];
  txMessage[length-2] = '.';
  
  txMessage[length + 1] = 'V';
  txMessage[length + 2] = '\0';
  
  softSerial.println(txMessage);
}

void initTxMessage(void)
{
  txMessage[0] = 'a';
  txMessage[1] = deviceID[0];
  txMessage[2] = deviceID[2];
}

uint8_t toString(unsigned int val, char * buf)
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
uint8_t getPlaceCount(unsigned int value, unsigned int place)
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

