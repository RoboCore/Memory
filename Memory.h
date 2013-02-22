#ifndef RC_MEMORY
#define RC_MEMORY

/*
	RoboCore Memory Library
		(v1.0 - 22/02/2013)

  Library to get the status of the memory (for Arduino 1.0 or later)

  Released under the Beerware licence
*/


#include "Arduino.h" //for Arduino 1.0 or later


//-------------------------------------------------------------------------------------------------

// Display the available memory
void AvailableMemory(HardwareSerial* serial);
void AvailableMemory(HardwareSerial* serial, boolean total);

//-------------------------------------------------------------------------------------------------

// Return the free space in RAM (in bytes)
//    NOTE: even after calling 'free()' __brkval might not decrease.
//            The memory block will nevertheless be marked as free.
int freeRAM();
int freeRAM(boolean total);

//-------------------------------------------------------------------------------------------------

// Calculates the size of the free list (thanks to Matthew Murdoch)
int freeListSize();

//-------------------------------------------------------------------------------------------------



#endif
