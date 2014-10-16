/*
 * See averager.h for class documentation
 */

/* Arduino Library Includes */
#include <Arduino.h>

/* Class Header */
#include "averager.h"

Averager::Averager(uint8_t n, int * pValues, int start)
{
	m_n = n;
	m_pValues = pValues;
	
	uint8_t i;
	for (i = 0; i < n; ++i) { m_pValues[i] = start; }
	
	m_next = 0;
}

Averager::~Averager()
{
	delete[] m_pValues;
}

void Averager::NewValue(int newValue)
{
	m_pValues[m_next++] = newValue;
	if(m_next == m_n) { m_next = 0; }
}

void Averager::Reset(int resetValue)
{
	uint8_t i;
	for (i = 0; i < m_n; ++i) { m_pValues[i] = resetValue; }
}

int Averager::GetAverage(void)
{
	unsigned long sum = 0UL;
	
	uint8_t i;
	for (i = 0; i < m_n; ++i)
	{
		sum += m_pValues[i];
	}
	
	return (int)(sum / m_n);
}
