#ifndef RC_MEMORY
#define RC_MEMORY

/*
	RoboCore Memory Library
		(v1.3 - 01/03/2013)

  Memory functions for Arduino
    (tested with Arduino 0022 and 1.0.1)

  Released under the Beerware license
  Written by François
  

The PointerList class implements static functionality to track
	allocated memory.
	# one must first Initialize the values
	# the tracker capacity is limited and can be changed in
		with POINTER_LIST_SIZE
	# macros 'Mmalloc()', 'Mfree()' and 'MReset()' defined
        # leave USE_POINTER_LIST defined to use this class
                (other libraries use this functionality if defined,
                otherwise use 'standard' malloc())
        !!! DO NOT use free() on pointers added to the list
*/

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h> //for Arduino 1.0 or later
#else
#include <WProgram.h> //for Arduino 22
#endif

//#define RC_MEM_DEBUG
#define USE_POINTER_LIST //define if want to use the Pointer List (or else comment this line)

// options for DisplayFreeList()
#define DISPLAY_HEAP_START (1 << 0)
#define DISPLAY_BRKVAL (1 << 1)
#define DISPLAY_SIZE (1 << 2)

//-------------------------------------------------------------------------------------------------

// Display the available memory
void AvailableMemory(HardwareSerial* serial);
void AvailableMemory(HardwareSerial* serial, boolean total);

//-------------------------------------------------------------------------------------------------

// Display the items in the Free List (with bitwise options)
void DisplayFreeList(HardwareSerial* serial, byte options);

//-------------------------------------------------------------------------------------------------

// Return the free space in RAM (in bytes)
//    NOTE: even after calling 'free()' __brkval might not decrease.
//            The memory block will nevertheless be marked as free.
int freeRAM(void);
int freeRAM(boolean total);

//-------------------------------------------------------------------------------------------------

// Calculates the size of the free list (thanks to Matthew Murdoch)
int freeListSize(void);

//-------------------------------------------------------------------------------------------------

// Check if using the Pointer List
boolean UsingPointerList(void);

//-------------------------------------------------------------------------------------------------
#ifdef USE_POINTER_LIST 

#define POINTER_LIST_SIZE 50

//macros with a different name to not confuse with malloc() and free()
#define Mmalloc(X) PointerList::Malloc(X)
#define Mfree(X) PointerList::Free(X)
#define MReset(X) PointerList::Reset(X)


class PointerList{
  private:
    static uint16_t _count;
    static void* _list[POINTER_LIST_SIZE];
    static boolean _initialized;
  
  public:
    static void DisplayList(HardwareSerial* printer);
    static void DisplayList(HardwareSerial* printer, uint8_t format);
    static boolean Free(void* ptr);
    static boolean FreeIndex(uint16_t index);
    static boolean FreeList(void);
    static void Initialize(void);
    static boolean isInitialized(void);
    static uint16_t ListCount(void);
    static void* Malloc(size_t size);
    static boolean Reset(void);
};

#endif //#ifdef USE_POINTER_LIST

#endif
