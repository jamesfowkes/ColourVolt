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

void setup() {

  pinMode(RED_PIN, OUTPUT);    
  pinMode(GRN_PIN, OUTPUT); 
  pinMode(BLU_PIN, OUTPUT);

  delay(1000); // Wait a bit before sending anything over serial
  
  messagingBegin(4800, DEVICE_ID_EEPROM_ADDRESS);

  sendVoltage(0);
  sendVoltage(1);
  sendVoltage(10);
  sendVoltage(100);
  sendVoltage(1000);
  sendVoltage(10000);
  sendVoltage(30000);
  
  // Give the calibration module its EEPROM address so it can read stored value
  Calib_setup(CALIBRATION_EEPROM_ADDRESS);

  // Make sure threshold is properly set before the LEDs are updated
  readRangeADCs();
}

void loop() 
{
  setLEDs(LOW, LOW, LOW);
  delay(1000);
  setLEDs(HIGH, LOW, LOW);
  delay(1000);
  /*
  if( newReadingReady )
  { 
    // There is a new ADC reading of the power input
    processNewReading();
    newReadingReady = false;
  }

  // Run the tasks
  readMainADCTask.tick();
  readRangeADCsTask.tick();

  handleSerialComms();*/
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

void handleRxMessage(char * message)
{
    if (messageEquals("V?"))
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


