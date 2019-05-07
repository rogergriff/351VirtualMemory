#ifndef HARDWARE_H
#define HARDWARE_H
#ifndef OS_H
#define OS_H
#include <iostream>
#include <fstream>
using namespace std;


//end of Memory Management Unit

int main() { //shouldn't we put main at the top, i mean, that's why we put in the .h files, so it knows all the functions and classes and structs that will be available, so we can just do main at the start.

  
  
}
  

// Header OS
  
// protected Class PRA
  

// From Class PRA
  
PRA::~PRA();

Word PRA::findVictim (){
  
};

Word PRA::getPRA (){
  
}; 

Word PRA::updateUsage(){
  
};

  
// from struct FIFO in Class PRA

Word PRA FIFO::findVictim(){

};
  
Word PRA FIFO::FIFO(); 
 
//From class LRU:public PRA
  
Word LRU::findVictim(){
  
};
  
LRU::LRU ();
  
void LRU::updateUsage(){

};
  
//From Class Memory Manager  
  
MM::MM ();
  
MM MM::instance(){
};
  
bool MM::operator=(){
};
  
void MM::pageIN(pageTable){
};
  
  
           //Header HARDWARE
  
  
  //class Memory Management Unit

//begin
//default constructor 
MemoryManagementUnit : MemoryManagementUnit()
{
	Page_AccCount = 0;
	Page_Faults = 0;
	TLB_AccCount = 0;
	TLB_Faults = 0;
}



//
int MemoryManagementUnit:: pageAccesses()
{
	
}


int MemoryManagementUnit:: pageFaults()
{
	
}



int MemoryManagementUnit:: TLB_Accesses()
{
	
}



int MemoryManagementUnit:: TLB_Accesses()
{
	//
	
}



int MemoryManagementUnit:: TLB_Faults()
{
	//counts how many tlb faults
}

/* 
In hardware.h it should be:
bool operator=( const MemoryManagementUnit& ) const;
*/

bool MemoryManagementUnit:: operator=( const MemoryManagementUnit & a ) const
{
	
}

//end of Memory Management Unit


//word

//backing store

BackingStore::BackingStore()
{

}

BackingStore:: ~BackingStore()
{

}

BackingStore BackingStore::instance()
{

}

bool BackingStore :: opertor=()
{

}

void BackingStore :: read()
{
	//cin from backingstore
}



//Ram

RAM:: RAM()
{

}

RAM RAM::instance()
{

}

//bool operator=();
Bool RAM::operator=()
{

}


//idk if this is correct
void RAM::read<T>()
{

}


//Status RAM::arrStatus( Status, int b)
{
	// Status
	frameSize = b;
}



