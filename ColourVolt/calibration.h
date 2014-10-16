#ifndef _CV_CALIBRATION_H_
#define _CV_CALIBRATION_H_

/**
 * This module handles ADC calibration by reference to an external voltage source
 
 * The module is intended to be used in products where the voltage on an ADC input has been scaled from another voltage.
 * The module allows a known voltage to be used in order to provide a scaling factor for converting ADC inputs to voltages.
 
 * The module requires two bytes of EEPROM memory to store the scaling factor.
 
 * The module should be initialised by calling Calibration_Setup:
    
	Calibration_Setup(CALIBRATION_ADDRESS);
	
 * where:
 * CALIBRATION_ADDRESS is the EEPROM address to read/write the calibration scaling factor
 
 * When this is called, the module will:
 *  - Read the calibration factor from EEPROM

 * To store a new scaling factor, the application should call Calibration_Start. This will put the module into calibration mode.
 * The module assumes that the ADC reading at calibration represents 10.000V (10000mV).
 * Therefore a voltage as close to this value as possible should be applied to the appropriate point in the circuit during calibration.
 * The application must then:
 *  - Take 100 ADC readings and pass them to the calibration module using Calibration_NewValue. For example:

    Calibration_Start();
    
    int i;
    for (i = 0; i < 100; i++)
    {
        int newValue = analogRead(adcPin);
        Calibration_NewValue(newValue);
        delay(20);
    }
    
  * The delay in the loop ensure that readings are taken over an extended period of time (in this case 20 * 100 = 2000ms).
  * The application developer should choose an appropriate time delay between readings.
  
  * When the 100th reading is given to the module, the module will:
  * - Calculate the average of the readings
  * - Store this average in EEPROM
  * - Come out of calibration mode
  
  * To assist the application developer, the Calibration_InProgress function is provided to determine when calibration is complete.
  * This may help when designing non-blocking applications.
  
  * To use the module to convert ADC readings to voltage, use Calibration_ToMilliVolts.
  * For example, if an ADC value of 333 represents a voltage of 10V, and the current reading is 506:
  
    int newValue = analogRead(adcPin); // newValue is 506 after this call
    int voltage = Calibration_ToMilliVolts(newValue) // voltage is 15195, representing 15.195V

  * If desired, the calibration value may be read using Calibration_GetValue.    
*/
  
void Calibration_Setup(int eepromAddress);
void Calibration_Start(void);
void Calibration_NewValue(int newValue);
bool Calibration_InProgress(void);
int Calibration_GetValue(void);
unsigned int Calibration_ToMilliVolts(unsigned int v);

#endif
