
#include <Memory.h>

//-------------------------------------------------------------------------------------------------



void setup(){
  Serial.begin(9600);
  
  Serial.print("Using Pointer List: ");
  if(UsingPointerList())
    Serial.println("OK");
  else
    Serial.println("no");
  Serial.println();
}



void loop(){
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  DisplayFreeList(&Serial, DISPLAY_HEAP_START | DISPLAY_BRKVAL | DISPLAY_SIZE);
  Serial.println("--- start ---");
  
  void* ptr = malloc(100);
  Serial.println((int)ptr, HEX);
  
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  void* ptr2 = malloc(200);
  Serial.println((int)ptr2, HEX);
  
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  free(ptr);
  free(ptr2);
  DisplayFreeList(&Serial, DISPLAY_HEAP_START | DISPLAY_BRKVAL | DISPLAY_SIZE);
  Serial.println("--- freed ---");
  
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  Serial.println("--- list test ---");
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  if(!PointerList::isInitialized())
    Serial.println("NOT initialized");
  else
    Serial.println("Initialized");
  
  PointerList::Initialize();
  
  void* Mptr1 = Mmalloc(100);
  void* Mptr2 = Mmalloc(200);
  void* Mptr3 = Mmalloc(100);
//  PointerList::Initialize();
  PointerList::DisplayList(&Serial, HEX);
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  Mfree(Mptr1);
  PointerList::FreeIndex(1);
  PointerList::DisplayList(&Serial, HEX);
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  Serial.println("* reset");
//  PointerList::Reset();
  MReset();
  PointerList::DisplayList(&Serial, HEX);
  AvailableMemory(&Serial);
  AvailableMemory(&Serial, true);
  
  DisplayFreeList(&Serial, DISPLAY_HEAP_START | DISPLAY_BRKVAL | DISPLAY_SIZE);
  Serial.println("--- FIM ---");
  while(1){
    delay(100);
  }
}






