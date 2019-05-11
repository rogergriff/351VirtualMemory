/*********************************
CPSC 351 Section 04
Group Members:	Roger Griffin
		Luisfernando Gomez
		Jimena Murillo
		TEAM #17
		
Operating System hpp file
*********************************/
/*
The operting system will contro the following in a virtual memory manager:
Page Replacement Algorithms:
	LRU and FIFO
Process Control Block
Memory Manager
Page Table Entry

*/
#ifndef OS_H
#define OS_H
#include <iostream>
#include <fstream>
#include "HARDWARE.h"
using namespace std;



/*class PRA{ //Page replacement algorithm
	struct FIFO {
		public:
			Word findVictim();
			FIFO(); // constructor
		private:
			Word front; // what's at the front and will therefore be booted next when it's full.
	};
  

	struct LRU: public PRA{
		public:
			Word findVictim();
			LRU();
			void updateUsage();
		private:
			LRUList;
	};
  	
	private:
		int options(); 	//use this to get the type of PRA wanted at run-time, 
				//so something like "what page replacemnt algorithm do
				//you want to use, 1 for fifo or 2 for lru
	protected:
		PRA(); //constructor for class
	public:
		~PRA(); //destructor
		Word findVictim();
		getPRA();
		updateUsage();
};
*/


/********** PAGE TABLE ENTRY **********/
struct PTE{
	int frameNumber = 0;	//frame number place holder initially 0
	bool valid = false;	//page table entry initially invalid 
};


/********** PROCESS CONTROL BLOCK **********/
struct PCB{
	PTE myPageTable[256];	//usually would contain more, but for this project a page tabel of 256 is all that is needed
}; 


/********* MEMORY MANGER *********/
class MM{ 
	private:
		//int freeFrames(); //which frames are free, if any??
		// MM(); //constructor??
		PCB pageTable;		//page table type PCB
	public:
		MM();			//constructor creates pcb
		tlbEntry readPageTable(int, MemoryManagementUnit&, RAM&,BackingStore&);	//reads the page table entry
		//MM instance();//?
		//bool operator=(); //?
		void pageIn(PTE[], int, RAM&, BackingStore&); //bring in page via demand paging (10.2 in book)
};



#endif
