#ifndef _CV_CALIBRATION_H_
#define _CV_CALIBRATION_H_

/*
	calibration.h
*/

void Calibration_Setup(int eepromAddress);
void Calibration_Start(void);
void Calibration_NewValue(int newValue);
bool Calibration_InProgress(void);
int Calibration_GetValue(void);
unsigned int Calibration_ToMilliVolts(unsigned int v);

#endif
