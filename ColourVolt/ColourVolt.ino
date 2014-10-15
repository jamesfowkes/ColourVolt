/*
ColourVolt

- Reads power supply voltage and outputs "within range" status via RGB LED
- Range is set by two potentiometers (for 'ideal' voltage and acceptable range)
- Serial connection allows calibration and diagnostics

- Target: ATTINY84
*/

/* Arduino Library Includes */
#include <EEPROM.h>
#include <SoftwareSerial.h>

/* Application Includes */
#include "calibration.h"
#include "messaging.h"

/* Defines */
#define RED_PIN 6
#define GRN_PIN 5
#define BLU_PIN 7

#define VOLTS_PIN A0
#define SETPOINT_PIN A1
#define RANGE_PIN A2

#define DEVICE_ID_EEPROM_ADDRESS 0x00 // 2 bytes
#define CALIBRATION_EEPROM_ADDRESS 0x02 // 2 bytes

// Index into s_counters for each task
#define MAIN_ADC 0
#define RANGE_ADCS 1
#define SETUP 2

// How often to run each "task" in milliseconds
#define MAIN_ADC_INTERVAL_MS 20
#define RANGE_ADC_INTERVAL_MS 100
#define SETUP_INTERVAL_MS 1500

// IDs for which reading to send over serial
#define LIVE_VOLTS_READ 0
#define SETPOINT_READ 1
#define RANGE_READ 2
#define HIGH_TH_READ 3
#define LOW_TH_READ 4

/* Private Variables */
static int s_voltageReading = 0;
static int s_lowThreshold = 0;
static int s_highThreshold = 0;
static int s_setpointReading = 0;
static int s_rangeReading = 0;

static bool s_newReadingReady = false;

static bool s_echoSetupInfo = false;

static unsigned long s_counters[3] = {0UL, 0UL, 0UL};

void setup() {

	pinMode(RED_PIN, OUTPUT);    
	pinMode(GRN_PIN, OUTPUT); 
	pinMode(BLU_PIN, OUTPUT);

	while (millis() < 1000)
	{
		// Wait a bit before sending anything over serial
		// or writing EEPROM
	}

	messagingBegin(4800, DEVICE_ID_EEPROM_ADDRESS);

	// Give the calibration module its EEPROM address so it can read stored value
	Calib_setup(CALIBRATION_EEPROM_ADDRESS);

	// Make sure threshold is properly set before the LEDs are updated
	readRangeADCs();
}

void loop() 
{
	unsigned long newmillis=millis();

	if( s_newReadingReady )
	{ 
		// There is a new ADC reading of the power input
		processNewReading();
		s_newReadingReady = false;
	}

	if ((newmillis - s_counters[MAIN_ADC]) > MAIN_ADC_INTERVAL_MS)
	{
		s_counters[MAIN_ADC] = newmillis;
		readMainADC();
	}

	if ((newmillis - s_counters[RANGE_ADCS]) > RANGE_ADC_INTERVAL_MS)
	{
		s_counters[RANGE_ADCS] = newmillis;
		readRangeADCs();
	}

	if ((newmillis - s_counters[SETUP]) > SETUP_INTERVAL_MS)    
	{
		s_counters[SETUP] = newmillis;
		if (s_echoSetupInfo)
		{
			sendReading(SETPOINT_READ);
			sendReading(RANGE_READ);
		}
	}
	
	handleSerialComms();

}

void processNewReading(void)
{
	if ( Calib_inProgress() )
	{
		// Update the calibration software - this has no effect unless calibration is running
		setLEDs(LOW, LOW, LOW);
		Calib_newValue(s_voltageReading); 
		
		if (!Calib_inProgress())
		{
			sendMessage("CAL. DONE");
		}
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
	if (s_voltageReading <= s_lowThreshold) // Below range
	{
		setLEDs(LOW, HIGH, HIGH); // Red
	}
	else if (s_voltageReading >= s_highThreshold) // Above range
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
	s_voltageReading = analogRead(VOLTS_PIN);
	s_newReadingReady = true;
}

void readRangeADCs(void)
{
	/* Reads the setpoint and range pots. and calculates new hi/lo thresholds */
	int newSetpointReading = analogRead(SETPOINT_PIN);
	int newRangeReading = analogRead(RANGE_PIN);

	if ((s_setpointReading != newSetpointReading) || (s_rangeReading != newRangeReading))
	{
		s_setpointReading = newSetpointReading;
		s_rangeReading = newRangeReading;
		// s_lowThreshold might go < 0, s_highThreshold might go > 1023
		// This doesn't really matter, just means that reading will never go outside of valid range!
		s_lowThreshold = s_setpointReading - (s_rangeReading / 2);
		s_highThreshold = s_setpointReading + (s_rangeReading / 2);
	}
}

void handleRxMessage(char * message)
{
	if (messageEquals("V?"))
	{
		sendReading(LIVE_VOLTS_READ);
	}
	else if (messageEquals("HT?"))
	{
		sendReading(HIGH_TH_READ);
	}
	else if (messageEquals("LT?"))
	{
		sendReading(LOW_TH_READ);
	}
	else if (messageEquals("SP?"))
	{
		sendReading(SETPOINT_READ);
	}
	else if (messageEquals("RNG?"))
	{
		sendReading(RANGE_READ);
	}
	else if (messageEquals("CAL"))
	{
		Calib_start();
	}
	else if (messageEquals("SETUP"))
	{
		s_echoSetupInfo = !s_echoSetupInfo;
	}
}

void sendReading(int reading_id)
{
	unsigned int voltage;
	
	switch (reading_id)
	{
	case LIVE_VOLTS_READ:
		voltage = Calib_toMilliVolts(s_voltageReading);
		sendVoltage(voltage);
		break;
	case SETPOINT_READ:
		voltage = (s_highThreshold + s_lowThreshold) / 2;
		voltage = Calib_toMilliVolts(voltage);
		sendVoltageWithPrefix("SP", voltage);
		break;
	case RANGE_READ:
		voltage = (s_highThreshold - s_lowThreshold);
		voltage = Calib_toMilliVolts(voltage);
		sendVoltageWithPrefix("RNG", voltage);
		break;
	case HIGH_TH_READ:
		voltage = Calib_toMilliVolts(s_highThreshold);
		sendVoltageWithPrefix("HT", voltage);
		break;
	case LOW_TH_READ:
		voltage = Calib_toMilliVolts(s_lowThreshold);
		sendVoltageWithPrefix("LT", voltage);
		break;		
	default:
		break;
	}
}