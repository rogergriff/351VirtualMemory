#ifndef HARDWARE_H
#define HARDWARE_H
#include <iostream>
#include <fstream>
using namespace std;

/*
// Memory Management Unit
class MemoryManagementUnit{ 
	struct PageFault {
		PageFault();
		Word pageNumber;
	}
	
	
	private:
		MemoryManagementUnit();
		int Page_AccCount;
		int Page_Faults;
		//tlb_ :TLB
		int TLB_AccCount;
		int TLB_Faults;

	public:
		void clearTLB(); //clear the buffer
		MemoryManagementUnit(); //initialize?
	
		MemoryManagementUnit( , );
	
		MemoryManagementUnit instance();
		MemoryManagementUnit operator=();
		pageAccesses();
		pageFaults();
		//void read<T>();
		TLB_Accesses();
		TLB_Faults();
}
*/
//class PageFault: public MMU{ 
//	// private:
//	public:
//		PageFault();
//		Word pageNumber;
//};

//Address nested in Word Struct

struct Word { 
	int unit;
	unit value_t;
	
	struct address {
		Word address();
		Word displacement();
		Word frame();
		Word page();
	}
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
class BackingStore{
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

/*
class RAM{
	struct Status {
		bool accessed;
		bool dirty;
	}vmProjectHWHeader //? whats this for?
	private:
		RAM();
		int frameSize = 256;
	public:
		RAM();
		RAM instance();
		RAM operator=();
		void read<T>();
		Status arrStatus [Status, frameSize]
};
*/

/*struct Status{
	bool accessed;
	Bool dirty;
}vmProjecrHWHeader*/
 
#endif
