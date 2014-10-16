#ifndef _AVERAGER_H_
#define _AVERAGER_H_

/**
 * This class is handles averaging a set of numbers.
	
 * In your programs, you create an averager like this:
    
	int numbers_to_average[N];
	Averager myAverager(N, numbers_to_average);
	
 * where:
 * numbers_to_average is the array where the numbers get stored.
 * N is the size of the array.
	
 * IMPORTANT: your code shouldn't ever write to this array, only create it for the averager to use.
 * The averager was designed this way to avoid using dynamic memory allocation.
 * This means you must know the size of the array at compile time.
	
 * When the class is created it will set all the numbers to be zero.
 * If you want the array initialized to a different number, you can call (for example):
	
    Averager myAverager(N, numbers_to_average, 5);
	
 * This is useful for setting a starting average.
	
 * Public class functions:
	void NewValue(int newValue) - Replaces the oldest value in the array with the provided number
	void Reset(int resetValue) - Writes the entire array with the provided number. Useful for initialization after starting.
	void GetAverage(void) - Returns the average of the numbers in the array
*/

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