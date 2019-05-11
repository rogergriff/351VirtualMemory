#ifndef HARDWARE_H
#define HARDWARE_H
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


// Memory Management Unit
struct tlbEntry{
int pageNumber = -1;
int frameNumber = -1;
};
struct Frame{
		void fillFrame(unsigned char[]);
		unsigned char readFrame(int);
		unsigned char data[256];
	
};

struct Status{
	int frameNumber;
	bool accessed = false;
	bool dirty = true;
};

struct Word { 
	int u_int;
	int uin32_t(uint32_t);
	

};
			
struct address {
		//Word address(); //we need to rename this somehow so it doesnt throw up an error constantly
		Word offset(uint32_t);
		//Word frame();
		Word page(uint32_t);
	};

class BackingStore{ //loads the contents of BACKING_STORE.bin to the program at the start i think
	private: 
		//BackingStore();
		
	public:
	
	BackingStore();
	~BackingStore();  //destructor
//	BackingStore instance();  //  in main.cpp:
 		//	BS BS::instance(  ){} 
//	BackingStore operator=();
	void read(int, Frame[]);
};
	
class RAM{ //where we're storing our frames/frames table i think
	private:
		//RAM();
		int frameSize = 256;
		Frame framesTable[256];
		Status arrStatus[256];
	public:
		RAM();
		//RAM instance();
		//RAM operator=();
		unsigned char read(int,int);
		int FreeFrames(int, BackingStore);
		//void frameIn(int);
};



class MemoryManagementUnit{ 
	/*struct PageFault {
		PageFault();
		Word pageNumber;
	}
	*/
	
	private:
	//	MemoryManagementUnit();
		int Page_AccCount;
		int Page_Faults;
		tlbEntry tBuffer[16]; //TLB
		int TLB_AccCount;
		int TLB_Faults;
		void clearTLB(); //clear the buffer
	public:
		MemoryManagementUnit(); //initialize?
	
		//MemoryManagementUnit( , );
	//
	//	MemoryManagementUnit instance();
	//	MemoryManagementUnit operator=();
		int pageAccesses();
		int pageFaults();
		void addPageAccesses();
		void addPageFaults();
		bool inTLB(int);
		int TLBAccesses();
		int TLBFaults();
		void addTLBAccesses();
		void addTLBFaults();
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

//class PageFault: public MMU{ 
//	// private:
//	public:
//		PageFault();
//		Word pageNumber;
//};

//Address nested in Word Struct

		


//// Word
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

//Backing Store





 
#endif
