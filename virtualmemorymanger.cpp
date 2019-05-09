#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "HARDWARE.h"
#include "OS.h"

#define FRAME_SIZE 256 // size of the frame
#define TOTAL_NUMBER_FRAMES 256 // total number of frames in physical memory






int main() { 
  
	int aSize = 0;
	int size = 999;
		
	vector<uint32_t> a(size);
	//Word page;  //delete before turning in if the program works
	Word offset;
	//int page;  //delete before turning in
	//int offset;	//delete before turning in	
	Word page_table_number;
	address add;
	MM memory;

    	ifstream myfile("addresses.txt");
	if(myfile.is_open())
	{
		while(true)
		{
			uint32_t x;
			myfile >> x;

			if (myfile.eof())
			{
				//cout << "breaking out after aSize=" << aSize << " because found eof.\n"; //debugging code
				break;
			}
		
			else if( !myfile.eof() )
			{
				a[aSize] = x;
				aSize++;

			}
			
			else
			{
				cout <<"error reading in addresses"; //should never get here, seeing how you should only ever find the eof, or find that its not eof
			}
				
		}
	}	

/*
	for (int i = 0; i < aSize; i++){
	cout<< a[i] <<" " <<endl;}
	cout << "aSize is " << aSize << endl;		
*/
	myfile.close();

		
/* dont know if this is how we're supposed to do this but this theoretical masks the bits to get the page and the offset. 
Then it shifts it by 8 to get the page table number. */	
		
	for (int i=0; i< aSize; i++) 
	{
		//page = 
		//offset = 
		page_table_number = add.page(i,a); //gets the number to use for the page table
		//cout << "got " << page_table_number.u_int << " from add.page(i,a) \t"; //debugging code
		//cout << "the vector looks like this: \n"; //debugging code
		//	for(int i=0; i<aSize; ++i)
		//		cout << a[i] << endl;
		page_table_number.u_int = page_table_number.u_int>>8; //shifting the result we got so that its an appropriate page number
		offset = add.offset(i,a); //get the offset to use for the frame
		//cout << page << endl;
		//cout << "page table number:" << page_table_number.u_int <<"\toffset:"<< offset.u_int<< endl;
		memory.readPageTable(page_table_number.u_int, unit);		
	}

//START
//IDK where exactly to put this but this is from the code Luis found to detect pagefaults and get a free frame
//This section will later involve the tlb
//I also don't know the object's/variable's name so I named them what they are .
		
	// first try to get page from TLB
    	int frameNumber = -1; 		//initialized to -1, will be used to tell if it's valid in the conditionals below
    
    	int i;  
		
	// look through page table, if contents of the table are invlad it will go for a frame number
    	for(i = 0; i < TotalCountofPageNumbers; i++)	// once tlb is implmeneted,this will be "tlb size"
	{	
		//if page number given exsists in the page table
        	if(List_of_pageNumbers_we_got_from_addrses[i] == pageTable)
		{   		
			//if page table is invalid, the allocate free frame
			if( page_table_contents = invalid)	 //if content of page table is invalid, it will allocate a free frame
			{						 
            			frameNumber = freeframetable[i];  	// then the frame number is extracted
                		pageNumber ++ 				//will increment pageNumber in order to go to the next page number 
				pagefault++;               		// pagefault increments later the TLBHit counter is incremented
				//tlbhit++				//once tlb is implemented, this will increment a tlb hit
        		}
    		}
    	}
	
	
    	// if the frameNumber was not found, then frameNumber will remain at -1
	//therefore if frameNumber = -1 then page was found
    	if(frameNumber == -1)
	{	
		//if frameNumber is still = -1 then pagetable content was valid
        	int i;   		// walk the contents of the page table
        	for(i = 0; i < firstAvailablePageTableNumber; i++)		//I dont understand this part so I didnt change it
		{
			if(pageTableNumbers[i] == pageNumber)			// if the page is found in those contents
			{         
        			frameNumber = pageTableFrames[i];          	// extract the frameNumber from its twin array
				noPageFaultCount++				//needed for the statistics
				//tlb_notAccessed++				//will be needed for tlb statistics
				//make the page table at this spot valid
			}
        	}
	    
		//if the page is valid but I'm assuming it is also empty, it will get a frame from the bin?
        	if(frameNumber == -1)				// if the page is not found in those contents
		{                    	
            		readFromStore(pageNumber);             		// page fault, call to readFromStore to get the frame into physical memory and the page table
            		pageFaults++;                          		// increment the number of page faults
            		frameNumber = firstAvailableFrame - 1;  	// and set the frameNumber to the current firstAvailableFrame index
       		}
    	}
    
	//the rest is the same as the original code
    	insertIntoTLB(pageNumber, frameNumber);  // call to function to insert the page number and frame number into the TLB

	value = physicalMemory[frameNumber][offset];  // frame number and offset used to get the signed value stored at that address
   
	printf("frame number: %d\n", frameNumber);
	printf("offset: %d\n", offset); 
    	// output the virtual address, physical address and value of the signed char to the console
    	printf("Virtual address: %d Physical address: %d Value: %d\n", logical_address, (frameNumber << 8) | offset, value);
//END of code Luis found
		
	cout << "page faults is " << unit.pageFaults() << "\t aSize is " << aSize << endl; 
	page_fault_rate = (static_cast<float> (unit.pageFaults())/static_cast<float> (aSize)) * 100;
	cout << "\n\n\n\n\n\n\nThe page fault rate was:" << page_fault_rate << "%\n";// << (unit.pageFaults()/aSize) * percent<<"%\n";
	//cout<< "The amount of TLB hit rate was:" << (unit.TLB_Accesses()/aSize)*100<<"%\n";
	return 0;

}



int Word::uin32_t(uint32_t x)
{
	u_int = static_cast<int> (x);
	return x;
}

Word address::page(int x, vector<uint32_t> a)
{
	Word p;
	p.u_int = p.uin32_t(a[x] & 65280); //bit masking so that we get only bits 15 through 8
	return p;
}

Word address::offset(int x, vector<uint32_t> a)
{
	Word o;
	o.u_int = o.uin32_t(a[x] & 255);
	return o;
}


// read in logical addresses from address.txt --- done 
// mask bits to get page number and offset ----- done 
	
//TLB Section
/*

	//go into page table array, page 0 to page 255
	// processControlBlock struct will contain the page table
	
	if there exsists a page table that corresponds with the page but invalid then we get a frame number
	{
		if not available == Page Fault
		{
			- Backingstore.bin will be used if there is a page fault
			- backingstore.bin is size 256
			- account for page fault
			- Ex: if we need pg.15 but it resulted in  page fault, in order to find it from the bin
			we can use 256 * 15 to find the beginning of the corresponding frame number
		}
	}
	
	will also implement page replacement algorithms

*/
		
//Frame number is allocated
	
//Go to required frame

//While in frame, use offset to go to the beginning of a specific line
	
//read out whatever is in that specific frame
	
	
  
/*
//OS header functions
PRA::~PRA();
*/
  
/*
Word PRA::findVictim (){
  
};
*/
  
/*
Word PRA::getPRA (){
  
}; 
*/
  
/*
Word PRA::updateUsage(){
  
};
*/
  
// from struct FIFO in Class PRA
  
/*
Word PRA FIFO::findVictim(){

};
  */
  
/*
Word PRA FIFO::FIFO(); 
*/ 
//From class LRU:public PRA
    
/*
Word LRU::findVictim(){
  
};
*/
  
/*
LRU::LRU ();
  */
  
/*
void LRU::updateUsage(){

};
  */
//From Class Memory Manager  
    
MM::MM()
{
	PCB block;
	//for(int i=0; i <256; ++i){ //code for debugging
	//cout << "for block.myPageTable[" << i << "].frameNumber we have a value of:" << block.myPageTable[i].frameNumber << endl;
	//cout << "for block.myPageTagle[" << i << "].valid we have a value of :" << block.myPageTable[i].valid << endl;
}

  
/*
MM MM::instance()
{

};
*/
    
/*
bool MM::operator=(){
};
*/
    
int MM::readPageTable(int x, MemoryManagementUnit& u)
{
	if(pageTable.myPageTable[x].valid == true)
	{
		cout<< "found entry for page " << x << endl;
		u.addPageAccesses();	
		return pageTable.myPageTable[x].frameNumber;
	}
	
	else if(pageTable.myPageTable[x].valid == false)
	{
		cout << "failed to find page " << x << ", using page in \n";	
		u.addPageFaults();	
		pageIn(pageTable.myPageTable, x);
		return readPageTable(x,u);
	}
	
	/*else
	cout << "error reading page table"<< endl;*/
	return 0;
}  

void MM::pageIn(PTE pageT[], int page)
{
	pageT[page].valid = true;
	cout << "went into page in and set valid for "<< page << endl;
}
  
          
//class Memory Management Unit
//begin
//default constructor

MemoryManagementUnit:: MemoryManagementUnit()
{
	Page_AccCount = 0;
	Page_Faults = 0;
	//TLB_AccCount = 0;
	//TLB_Faults = 0;
}



//
int MemoryManagementUnit::pageAccesses()
{
	return Page_AccCount;
}


int MemoryManagementUnit::pageFaults()
{
	return Page_Faults;
}

void MemoryManagementUnit::addPageAccesses()
{
	++Page_AccCount;
}

void MemoryManagementUnit::addPageFaults()
{
	++Page_Faults;
}

/*
int MemoryManagementUnit:: TLB_Accesses()
{
	return TLB_AccCount;	
}
*/

/*
void MemoryManagementUnit:: addTLB_Accesses()
{
	//
	
}
*/

/*
int MemoryManagementUnit:: TLB_Faults()
{
	return TLB_Faults;//counts how many tlb faults
}
*/
/*
void MemoryManagementUnit::addTLB_Faults

/* 
In hardware.h it should be:
bool operator=( const MemoryManagementUnit& ) const;

bool MemoryManagementUnit:: operator=( const MemoryManagementUnit & a ) const
{
	
}

//end of Memory Management Unit
*/


//word
/*
//backing store

BackingStore::BackingStore()
{

}
*/

/*
BackingStore:: ~BackingStore()
{

}
*/

/*
BackingStore BackingStore::instance()
{

}
*/

/*
bool BackingStore :: opertor=()
{

}
*/


/*
void BackingStore :: read()
{
	//cin from backingstore
}
*/

/*
//Ram

RAM:: RAM()
{

}
*/
/*
RAM RAM::instance()
{

}
*/
/*
//bool operator=();
Bool RAM::operator=()
{

}
*/
/*
//idk if this is correct
void RAM::read<T>()
{

}
*/
/*
//Status RAM::arrStatus( Status, int b)
{
	// Status
	frameSize = b;
}

*/
