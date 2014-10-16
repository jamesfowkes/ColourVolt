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
#include "averager.h"

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
#define LED_UPDATE 3

// How often to run each "task" in milliseconds
#define MAIN_ADC_INTERVAL_MS 20
#define RANGE_ADC_INTERVAL_MS 100
#define SETUP_INTERVAL_MS 1500
#define LED_UPDATE_INTERVAL_MS 250

#define AVERAGER_TIME_MS 1000
#define AVERAGER_N (AVERAGER_TIME_MS / MAIN_ADC_INTERVAL_MS)

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

static bool s_echoSetupInfo = false;

static unsigned long s_counters[4] = {0UL, 0UL, 0UL, 0UL};

static int s_averagerValues[AVERAGER_N];
static Averager averager(AVERAGER_N, s_averagerValues);

void setup() {

	pinMode(RED_PIN, OUTPUT);    
	pinMode(GRN_PIN, OUTPUT); 
	pinMode(BLU_PIN, OUTPUT);

	while (millis() < 1000)
	{
		// Wait a bit before sending anything over serial
		// or writing EEPROM
	}

	Messaging_Begin(4800, DEVICE_ID_EEPROM_ADDRESS);

	// Give the calibration module its EEPROM address so it can read stored value
	Calibration_Setup(CALIBRATION_EEPROM_ADDRESS);

	// Make sure threshold is properly set before the LEDs are updated
	readRangeADCs();

	// Set starting average
	s_voltageReading = analogRead(VOLTS_PIN);
	averager.Reset( s_voltageReading );

}
void loop() 
{
	unsigned long newmillis=millis();

	if ((newmillis - s_counters[LED_UPDATE]) > LED_UPDATE_INTERVAL_MS)
	{
		s_counters[LED_UPDATE] = newmillis;
		updateLED();
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
	
	Messaging_HandleSerialComms();

}

void updateLED(void)
{
	s_voltageReading = averager.GetAverage();
	
	if ( Calibration_InProgress() )
	{
		// Update the calibration software - this has no effect unless calibration is running
		setLEDs(LOW, LOW, LOW);
		Calibration_NewValue(s_voltageReading); 
		
		if (!Calibration_InProgress())
		{
			Messaging_SendMessage("CAL. DONE");
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
	averager.NewValue( analogRead(VOLTS_PIN) );
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

void APP_HandleReceivedMsg(const char * message)
{
    (void)message; // This application doesn't need to do anything with the message itself
	if (Messaging_MessageIsEqualTo("V?"))
	{
		sendReading(LIVE_VOLTS_READ);
	}
	else if (Messaging_MessageIsEqualTo("HT?"))
	{
		sendReading(HIGH_TH_READ);
	}
	else if (Messaging_MessageIsEqualTo("LT?"))
	{
		sendReading(LOW_TH_READ);
	}
	else if (Messaging_MessageIsEqualTo("SP?"))
	{
		sendReading(SETPOINT_READ);
	}
	else if (Messaging_MessageIsEqualTo("RNG?"))
	{
		sendReading(RANGE_READ);
	}
	else if (Messaging_MessageIsEqualTo("CAL"))
	{
		Calibration_Start();
	}
	else if (Messaging_MessageIsEqualTo("SETUP"))
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
		voltage = Calibration_ToMilliVolts(s_voltageReading);
		Messaging_SendVoltage(voltage);
		break;
	case SETPOINT_READ:
		voltage = (s_highThreshold + s_lowThreshold) / 2;
		voltage = Calibration_ToMilliVolts(voltage);
		Messaging_SendVoltageWithPrefix("SP", voltage);
		break;
	case RANGE_READ:
		voltage = (s_highThreshold - s_lowThreshold) / 2;
		voltage = Calibration_ToMilliVolts(voltage);
		Messaging_SendVoltageWithPrefix("RNG", voltage);
		break;
	case HIGH_TH_READ:
		voltage = Calibration_ToMilliVolts(s_highThreshold);
		Messaging_SendVoltageWithPrefix("HT", voltage);
		break;
	case LOW_TH_READ:
		voltage = Calibration_ToMilliVolts(s_lowThreshold);
		Messaging_SendVoltageWithPrefix("LT", voltage);
		break;		
	default:
		break;
	}
}