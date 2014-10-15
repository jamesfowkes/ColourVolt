#ifndef _CV_CALIBRATION_H_
#define _CV_CALIBRATION_H_

/*
	calibration.h
*/

void Calib_setup(int eepromAddress);
void Calib_start(void);
void Calib_newValue(int newValue);
bool Calib_inProgress(void);
int Calib_getValue(void);
unsigned int Calib_toMilliVolts(unsigned int v);

#endif
