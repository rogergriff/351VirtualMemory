#include <iostream>
#include <fstream>
using namespace std;

#include "HARDWARE.h"
#include "OS.h"






int main() { 
  
    ifstream myfile("addresses.txt");
	if(myfile.is_open()){
		int aSize = 0;
		int a[999];
		
		while(true){
			int x;
			myfile >> x;
			if (myfile.eof())
				break;
			else if(true){
			a[aSize] = x;
			aSize++;
			}
		

			else{
				cout <<"you fucked up";
			    }
				
				}
for (int i = 0; i < aSize; i++){
				cout<< a[i] <<" ";
				cout<<endl;}		
myfile.close();
		return 0;
}
}
	

// read in logical addresses from address.txt


// mask bits to get page number and offset
/* 	a "Word" type will be created

	
*/
	
//tlb

//go into page table array, page 0 to page 255
// processControlBlock struct will contain the page table
/*	if there then we get a frame number
	{
	
	}
	if not available == Page Fault{
		- Backingstore.bin will be used if there is a page fault
		- backingstore.bin is size 256
		- Ex: if we need pg.15 but it resulted in  page fault, in order to find it from the bin
			we can use 256 * 15 to find the beginning of the corresponding frame number
	}
	
*/
		
//Frame number is allocated
	
//Go to required frame
//While in frame, use offset to go to the beginning of a specific line
	

//read out whatever is in that specific frame
	
	
}
  

//OS header functions
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



