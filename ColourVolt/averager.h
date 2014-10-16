#ifndef _AVERAGER_H_
#define _AVERAGER_H_

class Averager
{
	public:
		Averager(uint8_t n, int * pValues, int start=0);
		~Averager();
		
		void NewValue(int newValue);
		void Reset(int resetValue);
		
		int GetAverage(void);
		
	private:
		uint8_t m_n;
		int * m_pValues;
		uint8_t m_next;
};

#endif