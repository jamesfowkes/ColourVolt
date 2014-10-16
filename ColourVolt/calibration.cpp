/*

	calibration.cpp
	
	- Calibrates colour-based 'voltmeter' ADC
	
*/

/* Arduino Library Includes */
#include <EEPROM.h>
#include <Arduino.h>

/* Defines */
#define NUMBER_OF_SAMPLES 100
#define VOLTAGE_AT_CALIBRATION_MV 10000UL

/* Private Varibles */
static int s_calibrationValue = 0;
static int s_eepromAddress = 0;

static int s_newValue = 0;
static int s_calibrationCount = 0;

static bool s_calibrating = false;

void Calibration_Setup(int eepromAddress)
{
	s_eepromAddress = eepromAddress;
	
	// Read high byte of calibration value from EEPROM
	s_calibrationValue = (int)EEPROM.read(eepromAddress) << 8;
	// Read low byte of calibration value from EEPROM
	s_calibrationValue += (int)EEPROM.read(eepromAddress + 1);
}

bool Calibration_InProgress(void)
{
   return s_calibrating; 
}

void Calibration_Start(void)
{
	// Reset the calibration logging variables and set flag to start logging again
	s_calibrating = true;
	s_calibrationCount = 0;
	s_newValue = 0;
}

void Calibration_NewValue(int newValue)
{
	if (s_calibrating)
	{
		// Just sum the new values here. Division is done when all samples collected
		s_newValue += newValue;
		s_calibrationCount++;
		
		if(s_calibrationCount == NUMBER_OF_SAMPLES)
		{
			// Stop logging after NUMBER_OF_SAMPLES calibrations and store new value
			s_calibrationValue = s_newValue / NUMBER_OF_SAMPLES;
			EEPROM.write(s_eepromAddress, (uint8_t)(s_calibrationValue >> 8)); // High byte
			EEPROM.write(s_eepromAddress + 1, (uint8_t)(s_calibrationValue & 0xFF)); // Low byte
			s_calibrating = false;			
		}
	}	
}

int Calibration_GetValue(void)
{
	return s_calibrationValue;
}

unsigned int Calibration_ToMilliVolts(unsigned int v)
{
	unsigned long result = (VOLTAGE_AT_CALIBRATION_MV * (unsigned long)v) / (unsigned long)s_calibrationValue;
	if (result > 65535) { result = 65535; }
	return (unsigned int)result;
}

