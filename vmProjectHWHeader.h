#ifndef HARDWARE_H
#define HARDWARE_H
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


// Memory Management Unit
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
		//tlb_ :TLB
	//	int TLB_AccCount;
	//	int TLB_Faults;
	public:
		//void clearTLB(); //clear the buffer
		MemoryManagementUnit(); //initialize?
	
		//MemoryManagementUnit( , );
	//
	//	MemoryManagementUnit instance();
	//	MemoryManagementUnit operator=();
		int pageAccesses();
		int pageFaults();
		void addPageAccesses();
		void addPageFaults();

	
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

struct Word { 
	int u_int;
	int uin32_t(uint32_t);
	

};
			
struct address {
		//Word address(); //we need to rename this somehow so it doesnt throw up an error constantly
		Word offset(int, vector<uint32_t>);
		//Word frame();
		Word page(int, vector<uint32_t>);
	};
			


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
/*
//Backing Store
class BackingStore{ //loads the contents of BACKING_STORE.bin to the program at the start i think
	private: 
		BackingStore();
		
	public:
	
	BackingStore();
	~BackingStore();  //destructor
	BackingStore instance();  //  in main.cpp:
 		//	BS BS::instance(  ){} 
	BackingStore operator=();
	void read();
};
*/
struct Frame{
	unsigned char data[256] = {};
};

struct Status{
	int frameNumber;
	bool accessed = false;
	bool dirty = true;
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
		//void read<T>();
		
		int checkArrStatusforDirty();
};



 
#endif
