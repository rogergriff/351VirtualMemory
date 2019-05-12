/*********************************
CPSC 351
Group Members:	Roger Griffin - Section 01
		Luisfernando Gomez - Section 04
		Jimena Murillo - Section 04
		TEAM #17
		
OPERATING SYSTEM HPP
*********************************/

/*
The operting system will contro the following in a virtual memory manager:
Page Replacement Algorithms:
	LRU and FIFO
Process Control Block
Memory Manager
Page Table Entry

*/

#ifndef OS_HPP
#define OS_HPP
#include <iostream>
#include <fstream>
#include "HARDWARE.hpp"
using namespace std;



/********** PAGE TABLE ENTRY **********/
struct PTE
{
    int frameNumber = 0;			/*frame number place holder initially 0 */
    bool valid = false;				/*page table entry initially invalid*/
};



/********** PROCESS CONTROL BLOCK **********/
struct PCB
{
	PTE myPageTable[256];			/*usually would contain more, but for this project a page tabel of 256 is all that is needed*/
}; 



/********* MEMORY MANAGER *********/
class MM
{ 
    private:
		PCB pageTable;									/*page table type PCB*/
	public:
		MM();										/*constructor creates pcb*/
		tlbEntry readPageTable(int, MemoryManagementUnit&, RAM&,BackingStore&);		/*reads the page table entry*/
		void pageIn(PTE[], int, RAM&, BackingStore&); 					/*bring in page via demand paging (10.2 in book)*/
};




#endif
