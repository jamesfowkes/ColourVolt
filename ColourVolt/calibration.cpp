/*

	calibration.cpp
	
	- Calibrates colour-based 'voltmeter' ADC
	
*/

/* Arduino Library Includes */
#include <EEPROM.h>
#include <Arduino.h>

/* Defines */
#define NUMBER_OF_SAMPLES 100
#define VOLTAGE_AT_CALIBRATION_MV 10000

/* Private Varibles */
int s_calibrationValue = 0;
int s_eepromAddress = 0;

int s_newValue = 0;
int s_calibrationCount = 0;

bool s_calibrating = false;

void Calib_setup(int eepromAddress)
{
	s_eepromAddress = eepromAddress;
	
	// Read high byte of calibration value from EEPROM
	s_calibrationValue = (int)EEPROM.read(eepromAddress) << 8;
	// Read low byte of calibration value from EEPROM
	s_calibrationValue += (int)EEPROM.read(eepromAddress + 1);
}

bool Calib_inProgress(void)
{
   return s_calibrating; 
}
void Calib_start(void)
{
	// Reset the calibration logging variables and set flag to start logging again
	s_calibrating = true;
	s_calibrationCount = 0;
	s_newValue = 0;
}

void Calib_newValue(int newValue)
{
	if (s_calibrating)
	{
		// Just sum the new values here. Division is done when all samples collected
		s_newValue += newValue;
		s_calibrationCount++;
		
		if(s_calibrationCount < NUMBER_OF_SAMPLES)
		{
			// Stop logging after NUMBER_OF_SAMPLES calibrations and store new value
			s_calibrationValue = s_newValue / NUMBER_OF_SAMPLES;
			EEPROM.write(s_eepromAddress, (uint8_t)(s_calibrationValue >> 8)); // High byte
			EEPROM.write(s_eepromAddress + 1, (uint8_t)(s_calibrationValue & 0xFF)); // Low byte
			s_calibrating = false;			
		}
	}	
}

int Calib_getValue(void)
{
	return s_calibrationValue;
}

unsigned int Calib_toMilliVolts(unsigned int v)
{
	return (VOLTAGE_AT_CALIBRATION_MV * v) / s_calibrationValue;
}
