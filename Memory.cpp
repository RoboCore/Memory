

/*
	RoboCore Memory Library
		(v1.3 - 01/03/2013)

  Memory functions for Arduino
    (tested with Arduino 0022 and 1.0.1)

  Copyright 2013 RoboCore (François) ( http://www.RoboCore.net )
  
  ------------------------------------------------------------------------------
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  ------------------------------------------------------------------------------
  

The PointerList class implements static functionality to track
	allocated memory.
	# one must first Initialize the values
	# the tracker capacity is limited and can be changed in
		'Memory.h'
	# macros 'Mmalloc()', 'Mfree()' and 'MReset()' defined
        # leave USE_POINTER_LIST defined to use this class
                (other libraries use this functionality if defined,
                otherwise use 'standard' malloc())
        !!! DO NOT use free() on pointers added to the list
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
extern unsigned int __heap_start; // = __bss_end

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

// Display the items in the Free List (with bitwise options)
void DisplayFreeList(HardwareSerial* serial, byte options){
  struct __freelist* current;

  //display header
  if(options & DISPLAY_HEAP_START){
    serial->print("*heap start: ");
    serial->println((int)&__heap_start, HEX);
  }
  if(options & DISPLAY_BRKVAL){
    serial->print("*brkval: ");
    serial->println((int)__brkval, HEX);
  }

  for (current = __flp; current; current = current->nx) {
    serial->print("\t>");
    if(options & DISPLAY_SIZE){
      serial->print((int)current, HEX);
      serial->print(" : ");
      serial->println(current->sz + 2);
    } else {
      serial->println((int)current, HEX);
    }
  }
}

//-------------------------------------------------------------------------------------------------

// Return the free space in RAM (in bytes)
//    NOTE: even after calling 'free()' __brkval might not decrease.
//            Nevertheless, the memory block will be marked as free.
int freeRAM(void){
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
int freeListSize(void) {
  struct __freelist* current;
  int total = 0;

  for (current = __flp; current; current = current->nx) {
    total += 2; /* Add two bytes for the memory block's header  */
    total += (int) current->sz;
  }

  return total;
}

//-------------------------------------------------------------------------------------------------

// Check if using the Pointer List
boolean UsingPointerList(void){
#ifdef USE_POINTER_LIST
  return true;
#else
  return false;
#endif
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
#ifdef USE_POINTER_LIST

boolean PointerList::_initialized = false; //initialize with false
uint16_t PointerList::_count;
void* PointerList::_list[POINTER_LIST_SIZE];

#define DEFAULT_FORMAT HEX

//-------------------------------------------------------------------------------------------------

// Displays the list with the default format
void PointerList::DisplayList(HardwareSerial* printer){
  DisplayList(printer, DEFAULT_FORMAT);
}


// Displays the list
void PointerList::DisplayList(HardwareSerial* printer, uint8_t format){
  //check if variables were initialized
  if(!_initialized)
    return;
  
  //if invalid format, use default format (HEX)
  if((format != HEX) && (format != DEC) && (format != OCT) && (format != BIN))
    format = DEFAULT_FORMAT;
  
#ifdef RC_MEM_DEBUG
  printer->print("> heap start : ");
  printer->println((int)&__heap_start, format);
#endif
  
  for(uint16_t i=0 ; i < POINTER_LIST_SIZE ; i++){
    if(_list[i] != NULL){
      printer->println((int)_list[i], format);
    }
  }
}

//-------------------------------------------------------------------------------------------------

// Frees and removes a given pointer from the list
boolean PointerList::Free(void* ptr){
  //check if variables were initialized
  if(!_initialized)
    return false;
  
  // DO NOT free a NULL pointer
  if(ptr == NULL)
    return true;
  
  for(uint16_t i=0 ; i < POINTER_LIST_SIZE ; i++){
    if(_list[i] == ptr){ //found the pointer
      free(ptr); //free the pointer
      _list[i] = NULL;
      _count--;
      break;
    }
  }
  
  return true;
}

//-------------------------------------------------------------------------------------------------

// Frees a pointer from the list from the desired index (0 based) and removes it
boolean PointerList::FreeIndex(uint16_t index){
  //check if variables were initialized
  if(!_initialized)
    return false;
  
  if(index >= POINTER_LIST_SIZE)
    return false;
  
  //only decrement counter if the pointer at given index isn't null
  if(_list[index] != NULL){
    free(_list[index]); //free the pointer
    _list[index] = NULL;
    _count--;
  }
  
  return true;
}

//-------------------------------------------------------------------------------------------------

// Frees the list
boolean PointerList::FreeList(void){
  //check if variables were initialized
  if(!_initialized)
    return false;
  
  for(uint16_t i=0 ; i < POINTER_LIST_SIZE ; i++){
    if(_list[i] != NULL){
      free(_list[i]); //free the pointer
      _list[i] = NULL;
    }
  }
  _count = 0; //reset
  
  return true;
}

//-------------------------------------------------------------------------------------------------

// Initialize the static values
void PointerList::Initialize(void){
  //check if variables were initialized
  if(_initialized)
    return;
  
  _count = 0;
  for(uint16_t i=0 ; i < POINTER_LIST_SIZE ; i++)
    _list[i] = NULL;
  _initialized = true;
}

//-------------------------------------------------------------------------------------------------

// Check if values were initialized
boolean PointerList::isInitialized(void){
  return _initialized;
}

//-------------------------------------------------------------------------------------------------

// Get the number of allocate pointers in the list
uint16_t PointerList::ListCount(void){
  return _count;
}

//-------------------------------------------------------------------------------------------------

// Allocates a pointer and adds it to the list
void* PointerList::Malloc(size_t size){
  //check if variables were initialized
  if(!_initialized)
    return NULL;
  
  //find an empty space in the list
  uint16_t empty_index = 0;
  boolean found_empty = false;
  for(uint16_t i=0 ; i < POINTER_LIST_SIZE ; i++){
    if(_list[i] == NULL){ //found empty space
      empty_index = i;
      found_empty = true;
      break;
    }
  }
  
  //return null pointer if list is full
  if(!found_empty)
    return NULL;
  
  void* ptr = malloc(size); //allocate the space
  
  //add to the list if valid pointer
  if(ptr != NULL){
    _list[empty_index] = ptr;
    _count++;
  }
  
  return ptr;
}

//-------------------------------------------------------------------------------------------------

// Reset the static values
boolean PointerList::Reset(void){
  //check if variables were initialized
  if(!_initialized)
    return false;
  
  FreeList(); //free all pointers
  _initialized = false; //reset
  
  return true;
}

//-------------------------------------------------------------------------------------------------


#endif //#ifdef USE_POINTER_LIST







