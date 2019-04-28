#ifndef HARDWARE_H
#define HARDWARE_H
#include <iostream>
#include <fstream>
using namespace std;

//header file for the hardware portion
/*class HW{
	private: 

	public:
};*/

// Memory Management Unit
class MemoryManagementUnit{ 
 	private:
		MemoryManagementUnit();
		int Page_AccCount;
		int Page_Faults;
		//tlb_ :TLB
		int TLB_AccCount;
		int TLB_Faults;

	public:
		void clearTLB();
		MemoryManagementUnit();
		MemoryManagementUnit(char, char);
		MemoryManagementUnit instance();
		MemoryManagementUnit operator=();
		pageAccesses();
		pageFaults();
		//void read<T>();
		TLB_Accesses();
		TLB_Faults();
}

class PageFault: public MMU{ 
	// private:
	public:
		PageFault();
		Word pageNumber;
};



// Word
class Word{
	public:
		int unit;
		unit value_t;
};


//Address
class Address: public Word{ 
public: 
Word address();
Word displacement()
Word frame();
Word page();		

};

//Backing Store
class BackingStore{
	private: 
		BackingStore();
		
	public:
BackingStore();
~BackingStore();  //destructor

BackingStore instance();  /*  in main.cpp:
 			BS BS::instance(  ){} */

BackingStore operator=();
void read(char);
};

class RAM{
	private:
		RAM();
		int frameSize;
	public:
		RAM();
RAM instance();
		RAM operator=();
		void read<T>();
		Status arrStatus < Status, frameSize >
};

struct Status{
	bool accessed;
	Bool dirty;
}
 
#endif
