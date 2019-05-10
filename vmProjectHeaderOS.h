#ifndef OS_H
#define OS_H
#include <iostream>
#include <fstream>
#include "HARDWARE.h"
using namespace std;


//this will be the header file for the OS part our project


/*
//PAGE REPLACEMENT ALGORITHMS
class PRA
{ 	
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
        	int options(); //use this to get the type of PRA wanted at run-time, so something like "what page replacemnt algorithm do you want to use, 1 for fifo or 2 for lru
    	protected:
        	PRA(); //constructor for class
	public:
        	~PRA(); //destructor
        	Word findVictim();
        	getPRA();
        	updateUsage();
  };
*/


//PAGE TABLE ENTRIES
struct PTE{ 
	int frameNumber = 0;
	bool valid = false;
};



//PROCESS CONTROL BLOCK
struct PCB{ 
	PTE myPageTable[256];
}; //usually would contain more, but this is all we care about for the project




//MEMORY MANAGER FOR OS
class MM{ 
	private:
		//int freeFrames(); //which frames are free, if any??
		// MM(); //constructor??
        	PCB pageTable;
	public:
        	MM(); //constructor creates pcb
		int readPageTable(int, MemoryManagementUnit&, RAM&);
        	//MM instance();//?
        	//bool operator=(); //?
        	void pageIn(PTE[], int,RAM&); //bring in page via demand paging, see 10.2 in book
};

#endif
