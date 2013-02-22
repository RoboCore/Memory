

/*
	RoboCore Memory Library
		(v1.0 - 22/02/2013)

  Library to get the status of the memory (for Arduino 1.0 or later)

  Released under the Beerware licence
*/


#include "Memory.h"


//-------------------------------------------------------------------------------------------------

// The free list structure as maintained by the avr-libc memory allocation routines.
struct __freelist {
  size_t sz;
  struct __freelist *nx;
};


// The head of the free list structure
extern struct __freelist *__flp;


extern int *__brkval;
extern unsigned int __heap_start;

//-------------------------------------------------------------------------------------------------

// Display the available memory
void AvailableMemory(HardwareSerial* serial){
  serial->print("[mem] ");
  serial->println(freeRAM());
}


void AvailableMemory(HardwareSerial* serial, boolean total){
  serial->print("[mem] ");
  serial->println(freeRAM(total));
}

//-------------------------------------------------------------------------------------------------

// Return the free space in RAM (in bytes)
//    NOTE: even after calling 'free()' __brkval might not decrease.
//            Nevertheless, the memory block will be marked as free.
int freeRAM(){
  int v;
  return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

int freeRAM(boolean total){
  int free_memory;
  free_memory = (int)&free_memory - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
  
  if(total)
    free_memory += freeListSize();
  
  return free_memory;
}

//-------------------------------------------------------------------------------------------------

// Calculates the size of the free list (thanks to Matthew Murdoch)
int freeListSize() {
  struct __freelist* current;
  int total = 0;

  for (current = __flp; current; current = current->nx) {
    total += 2; /* Add two bytes for the memory block's header  */
    total += (int) current->sz;
  }

  return total;
}

//-------------------------------------------------------------------------------------------------







