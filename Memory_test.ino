
#include "Memory.h"

//-------------------------------------------------------------------------------------------------


extern int __heap_start;
extern int* __brkval;


void setup(){
  Serial.begin(9600);
}



void loop(){
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  void* ptr = malloc(100);
  Serial.println((int)ptr);
  
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  void* ptr2 = malloc(200);
  Serial.println((int)ptr2);
  
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  free(ptr);
  free(ptr2);
  Serial.println("--- freed ---");
  
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  Serial.println("--- FIM ---");
  
  while(1){
    delay(100);
  }
}






