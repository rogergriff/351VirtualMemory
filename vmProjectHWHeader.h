/*********************************
CPSC 351 Section 04
Group Members:	Roger Griffin
		Luisfernando Gomez
		Jimena Murillo
		TEAM #17
		
Hardware hpp file
*********************************/
/*
Hardware controls the following:
Memory Management Unit
Page Faults
Word
Addresses
Backing Store
Ram
*/


#ifndef HARDWARE_H
#define HARDWARE_H
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;



/********** WORD **********/
//Word: 
struct Word { 
	int u_int;
	int uin32_t(uint32_t);
};



/********** ADDRESS **********/
//Address: Members of this struct are type Word
struct address {
		//Word address(); //we need to rename this somehow so it doesnt throw up an error constantly
		Word offset(uint32_t);	//at this function, the logical address will be masked to find the offset 
		//Word frame();
		Word page(uint32_t);	//at this function, the logical address will be masked to identify the page number
};



/********** BACKING STOE **********/
//Loads the needed frames from the Backing_Store.bin file
//will only be used when a page fault occurs
class BackingStore{ 
	private: 
		//BackingStore();
		
	public:
		BackingStore();			//constructor - will open the binary file
		~BackingStore();  		//destructor - will close the binary file once read from
		//BackingStore instance();  	
 		//BS BS::instance(  ){} 
		//BackingStore operator=();
		void read(int, Frame[]);	//function used to read from the backing_store bin, will recieve an int and the frame eing worked on 
};



/********** FRAME **********/
// will be used in the class type RAM
struct Frame{
	void fillFrame(unsigned char[]);	//fills a single frame with an unsigned char once the char is pulled from memory or bin file
	unsigned char readFrame(int);		//
	unsigned char data[256];		
};



/********** Status **********/
//Status: Monitors if a speific frame number was been accessed (read or written too)
//and if its considered dirty
//will be used in the class type RAM
struct Status{
	int frameNumber;		//holds the specific frame number being worked on
	bool accessed = false;		//set at false but if read or written during mnitoring interval, will be set to true
	bool dirty = true;		//set as true until the content is newer than that of the backing store
};



/********** RAM	**********/
//Frames will be stored and updated into RAM class
class RAM{ 
	//private:		//should this section be private??	
		//RAM();
		int frameSize = 256;		//frame size of 256
		Frame framesTable[256];		//frame table of struct type frame
		Status arrStatus[256];		//array keeps track of the status for the corresonding frame number
	public:
		RAM();
		//RAM instance();
		//RAM operator=();
		unsigned char read(int,int);		//read the unsigned char help in the frame
		int FreeFrames(int, BackingStore);	//free frames will be returned to be used when there is a page fault
		//void frameIn(int);
};


/********** TLB ENTRIES **********/
//This struct will monitor the page number and frame number of the TLB entries
struct tlbEntry{
	int pageNumber = -1;	//All 16 TLB entries will contain a page number
	int frameNumber = -1;	//each TLB entry will also contain a frame number
};



/********** MEMOR MANAGEMENT UNIT **********/
//
class MemoryManagementUnit{ 
	/*struct PageFault {		//DELETE
		PageFault();
		Word pageNumber;
	}
	*/
	
	private:
	//	MemoryManagementUnit();	//DELETE
		int Page_AccCount;		//will contain the count of how many times a page has been accessed
		int Page_Faults;		//will keep count of the times a page fault occurs
		tlbEntry tBuffer[16]; //TLB	//array of type tlb entries
		int TLB_AccCount;		//keeps count of how many times the TLB is accessed
		int TLB_Faults;			//keeps count of the TLB faults
		void clearTLB(); 		//clears the buffer
	
	public:
		MemoryManagementUnit(); 	//Memory Mangement Unit cnstructor
		//MemoryManagementUnit( , );
		//MemoryManagementUnit instance();
		//MemoryManagementUnit operator=();
		
		int pageAccesses();		//returns the count of how many times the pge was accessed
		int pageFaults();		//returns the count of the pge faults that occured
		void addPageAccesses();		//increments the count for page accesses
		void addPageFaults();		//increments the count for pagefaults
		bool inTLB(int);		//
		int TLBAccesses();		//returns the count of TLB accesses
		int TLBFaults();		//returns the count of TLB faults
		void addTLBAccesses();		//increments the count of TLB accesses
		void addTLBFaults();		//increments the count of TLB faults
		
		void Replace(tlbEntry);		
		void updateUsageLRU(tlbEntry);
		//tlbEntry readPageTable(int, MemoryManagementUnit&, RAM&);
		int readTLBTable(int);
		
		//void pageIn(TLBentries[]. int, RAM&)	
		//void read<T>();
		//int TLB_Accesses();
		//int TLB_Faults();
		//void addTLB_Accesses();
		//void addTLB_Faults();
};


//DELETE
//class PageFault: public MMU{ 
//	private:
//	

//	public:
//		PageFault();
//		Word pageNumber;
//};



//Address nested in Word Struct
// Word
//class Word{
//	public:
//		int unit;
//		unit value_t;
//};



////Address
//class Address: public Word{
//public: 
//	Word address();
//	Word displacement()
//	Word frame();
//	Word page();		
//};


#endif
