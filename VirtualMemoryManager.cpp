/*********************************
CPSC 351
Group Members:	Roger Griffin - Section 01
		Luisfernando Gomez - Section 04
		Jimena Murillo - Section 04
		TEAM #17
		
MAIN CPP
*********************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <iomanip>
using namespace std;

#include "HARDWARE.hpp"
#include "OS.hpp"

#define FRAME_SIZE 256 			//size of the frame
#define TOTAL_NUMBER_FRAMES 256 	// total number of frames in physical memory


/********** MAIN *********/
int main()
{ 	
	int aSize = 0;			//Measuered size of file, incremented after each time an address is read in
	Word offset;			//name for the offset thatwill be obtained
	Word page_table_number;		 
	address add;			
	MM memory;			
	MemoryManagementUnit unit;
	RAM ram;
	float page_fault_rate;		//variable that wil hold the final page fault rate for statitics
	float tlb_hit_rate;		//varible that will hold the final TLB hit rate
	int frame;			
	int o;				
	tlbEntry e;			
	BackingStore b;			
	
	
	cout << "Logical Address \tPhysical Address \tUnsigned Byte Value\n";
    	ifstream myfile("addresses.txt");		//read from "address.txt"
	ofstream output("output.txt");			//output to "otput.txt"
	
	if(myfile.is_open())				//file opens
	{	
		while(true)				//while open, read in from file
		{
			uint32_t x;
			myfile >> x;
			if (myfile.eof())		//Break out of file when reaches end
			{
				break;
			}

			else if(!myfile.eof())		//if it isn't the end, increment aSize
			{
				aSize++;		
			}
		
			else
			{
				cout <<"error reading in addresses"; 			//output error, shouldn't eer reach this point
			}
			
			page_table_number = add.page(x);				//gets the number to use for the page table
			page_table_number.u_int = page_table_number.u_int>>8; 		//shifting the result we got so that its an appropriate page number
			offset = add.offset(x);						//gets the offset to use for the frame
			o = offset.u_int;
			
			if(unit.inTLB(page_table_number.u_int)) 			//If found in TLB continue with the following instructions
			{
				unit.addTLBAccesses();					//add to TLB access count
				frame = unit.readTLBTable(page_table_number.u_int);	//use the frame number to take the info from the frame table
			}
				
			else								//If not found in the TLB, look for it in the page table
			{
				unit.addTLBFaults();							//add to TLB fault count
				e = memory.readPageTable(page_table_number.u_int, unit, ram, b);	//Reads the page table
				unit.Replace(e);							//Replace the tlb if page not found
				frame = e.frameNumber;		
			}
			
			unsigned char m = ram.read(frame,o);						//sets a the unsigned char to a value to allow it to be output(wasn't working otherwise.)
			cout << e.pageNumber << "\t\t" << e.frameNumber << "\t\t" << m << endl;		//prints out page corresponding page num and frame num
		}
		
		cout << "page faults is " << unit.pageFaults() << "\t aSize is " << aSize << endl;		//prints out page fault and the page at which it occured
		page_fault_rate = (static_cast<float> (unit.pageFaults())/static_cast<float> (aSize)) * 100;	//calculte page fault rte
		cout << "\n\n\n\n\n\n\nThe page fault rate was:" << page_fault_rate << "%\n";			//prints out page fault rate

		tlb_hit_rate = (static_cast<float> (unit.TLBAccesses())/static_cast<float> (aSize)) * 100; 	//calcuates TLB hit rate
		cout << "The TLB Hit rate was:" << tlb_hit_rate << "%\n";					//printsout TLB rate
	}
	
	myfile.close();		//closes file
	output.close();		//closes output.txt since we're done writing to it
	return 0;	

}

/********** END OF MAIN **********/



/********** UINT32_t - HARDWARE **********/
int Word::uin32_t(uint32_t x)
{
	u_int = static_cast<int> (x);		//casting from type uint32_t to int
	return x;			
}

/********** PAGE - HARDWARE **********/
//masking logical address to find page number
Word address::page(uint32_t a)
{
	Word p;
	p.u_int = p.uin32_t(a & 65280); 	//bit masking so that we get only get page bits 15 through 8
	return p;
}

/********** OFFSET - HARDWARE **********/
//masking logical address to fine offset
Word address::offset(uint32_t a)
{
	Word o;
	o.u_int = o.uin32_t(a & 255);		//bit masking to get offset bits 0 to 7
	return o;
}



/********** MEMORY MANAGER - 0S **********/
MM::MM()
{
	PCB block; 					//create our Process Control Block in the MM
	//for(int i=0; i <256; ++i){ 			//code for debugging
	//cout << "for block.myPageTable[" << i << "].frameNumber we have a value of:" << block.myPageTable[i].frameNumber << endl;
	//cout << "for block.myPageTagle[" << i << "].valid we have a value of :" << block.myPageTable[i].valid << endl;
}




/********** READ PAGE TABLE **********/
//Not in the MMU, but uses hardware parameters
tlbEntry MM::readPageTable(int x, MemoryManagementUnit& u, RAM& r, BackingStore& b)
{
	tlbEntry e;					//uses hardware- tlb entry from MMU is set
	if(pageTable.myPageTable[x].valid == true)	//if the page number is valid then it is in the table then continue
	{
		u.addPageAccesses();					//page accesses count is incremented
		e.frameNumber = pageTable.myPageTable[x].frameNumber;	//getting the corresponding frame number that is in the page table for that page
		e.pageNumber = x;					//setting getting the page that it is associated with, since it was passed its really easy 
		return e;						//
	}

	else if(pageTable.myPageTable[x].valid == false)		//is page number not valid in the table then continue with the following
	{
		u.addPageFaults();					//add page fault
		pageIn(pageTable.myPageTable, x, r,b);			//if the value isn't in the page table, we need to page it into the page table
		return readPageTable(x,u,r,b);				//recursive call to verify that it was input
	}
	return e;					

} 
 


/********** PAGE IN - OS **********/
void MM::pageIn(PTE pageT[], int page, RAM& r,BackingStore& backing)
{
	pageT[page].frameNumber = r.FreeFrames(page,backing);	//Since it wasn't in the page table, need to link it to a frame from the free frames available
	pageT[page].valid = true;				//Set valid bit to true so we know its a valid page and can thus be used in the future.
}
           


/********** MEMEORY MANAGEMENT UNIT CONSTRUCTOR - HARDWARE**********/
MemoryManagementUnit::MemoryManagementUnit(){
	Page_AccCount = 0;				//initialize page access count to 0
	Page_Faults = 0;				//initializes page fault count to 0
	clearTLB();					//clears TLB
}


/********** IN TLB - HARDWARE **********/
bool MemoryManagementUnit::inTLB(int x)			//Checks if an entry is in the TLB
{
	for(int i = 0; i < 16; ++i)
	{
		if(tBuffer[i].pageNumber == x)		//reading the buffer and checking if the page number is equal to the page we are looking for
		return true;				//it is, so return that it was found.
	}
	
	return false;					//wnt through the whole TLB and didnt find it
}



/********** PAGE ACCESSES - HARDWARE **********/
//returns count value for times the page table ws accessed
int MemoryManagementUnit::pageAccesses()
{
	return Page_AccCount;
}



/********** PAGE TABLE - HARDWARE **********/
//returns the page table faults count value
int MemoryManagementUnit::pageFaults()
{
	return Page_Faults;
}


/********** ADD PAGE ACCESSES - HARDWARE **********/
//increments the count of page accesses
void MemoryManagementUnit::addPageAccesses()
{
	++Page_AccCount;
}


/********** ADD PAGE FAULTS - HARDWARE **********/
//increments the the count of page faults
void MemoryManagementUnit::addPageFaults()
{
	++Page_Faults;
}



/********** TLB ACCESSES - HARDWARE **********/
//returns the count vlue for the times TLB was accessed
int MemoryManagementUnit:: TLBAccesses()
{
	return TLB_AccCount;	
}


/********** ADD TLB ACCESSES - HARDWARE **********/
//increments the count for TLB accesses
void MemoryManagementUnit:: addTLBAccesses()
{
	++TLB_AccCount;	
}


/********** TLB FAULTS - HARDWARE **********/
//returns the count value of TLB fats
int MemoryManagementUnit:: TLBFaults()
{
	return TLB_Faults;
}



/********** ADD TLB FAULTS - HARDWRAE **********/
//incremets count for TLB faults
void MemoryManagementUnit::addTLBFaults()
{
	++TLB_Faults;
} 



/********** READ TLB TABLE - HARDWRAE **********/
int MemoryManagementUnit::readTLBTable(int x)
{
	tlbEntry e;
	for(int i = 0; i < 16; ++i)
	{
		if(tBuffer[i].pageNumber == x)
		{
			e = tBuffer[i];
			updateUsageLRU(e);  		//comment out this line to change from LRU to FIFO
			return e.frameNumber;			
		}	
	}
	return 0;
}



/********** UPDATE USAGE LRU - HARDWARE **********/
//TLB replacement algorithms - LRU
void MemoryManagementUnit::updateUsageLRU(tlbEntry x)
{
	for(int i = x.pageNumber; i<15; ++i)
	{
		tBuffer[i].pageNumber = tBuffer[i+1].pageNumber;	//shift the TLB up one unit from the unit that was found so that we can put the found entry at the bottom since it is now the most recently used
		tBuffer[i].frameNumber = tBuffer[i+1].frameNumber;	//^
	}
	tBuffer[15] = x;						//putting the entry we found at the bottom
}
  

/********** REPLACE - HARDWARE **********/
//TLB replcement algorithm - FIFO
void MemoryManagementUnit::Replace(tlbEntry e)
{
	for(int i = 0; i < 15; i++)
	{
		tBuffer[i] = tBuffer[i+1];	//Shifting the whole TLB up 1 value to insert the new value at the bottom, the First one input or least recently used one are shifted out
	}
	
	tBuffer[15] = e;			//new last entry added
}


/********** CLEAR TLB **********/
//clears TLB entries
void MemoryManagementUnit::clearTLB()
{
	for(int i = 0; i < 16; ++i)
	{
		tBuffer[i].pageNumber = -1;	//clearing the tlb, so setting pageNumber and frameNumber to something we should never index
		tBuffer[i].frameNumber = -1;	
	}
}



/********** BACKING STORE CONSTRUCTOR - HARWARE **********/
BackingStore::BackingStore()
{
	//Should open the backing_store.bin here

}



/********** ~BACKING STORE DESTRUCTOR - HARDWARE **********/
BackingStore:: ~BackingStore()
{
	//should cloe the backing_store.bin file
}



/********** READ - HARWARE **********/
//reads from the backing_store.bin file
void BackingStore :: read(int p, Frame fT[256])	
{
	int y = p*256;							//completely useless, go ahead and DELETE
	ifstream file;							//creating a variable file of type fstream to do multiple different fstream functions on
	file.open("BACKING_STORE.bin", ios::in|ios::binary);		//Opens binary file	
	if(file.is_open())
	{				
		file.seekg(y);						//seeks bin file
		char * buffer = new char [256];				//allocate new memory to read the file into
		unsigned char * buff = new unsigned char [256];		//allocate new memory to reinterpret cast the data read from file
		file.read(buffer,256);					//reads buffer						
		buff = reinterpret_cast<unsigned char*> (buffer);		//converts signed chars to unsigned char
		fT[p].fillFrame(buff);	
	}						//filling frames table entry with the frame we just got
	file.close();							//closes binary file
}




/********** RAM - HARDWARE **********/
//Ram
RAM::RAM()
{
	for(int i = 0; i<256; ++i)
	{
		arrStatus[i].frameNumber = i;		//initializes the frames table array........
	}
}




/********** READ - HARDWARE **********/
unsigned char RAM::read(int f, int o)
{
	return framesTable[f].readFrame(o);		//returns physical memory from frame table
}



/********** READ FRAME - HARDWARE **********/
unsigned char Frame:: readFrame(int o)
{
	return data[o];					//return
	return 0;					//return
}



/********** FREE FRAMES - HARDWRAE **********/
//Uses hardware to inform if the frame is dirty
int RAM::FreeFrames(int p, BackingStore b) 
{
	for (int i = 0; i < 256; ++i)
	{
		if(arrStatus[i].dirty == true)	
		{	
			b.read(p, framesTable);			//reads frame table
			arrStatus[i].dirty = false;		//updated the frames table, from backingstore file, so sets dirty to false
			arrStatus[i].accessed = false;		//^
			return i;
		}
	}	
	return 0;
}



/********** FILL FRAME - HARDWARE **********/
//used to get free frame
void Frame::fillFrame(unsigned char x[])
{
	for(int i = 0; i<256; ++i)
	{
		data[i] = x[i];
	}
}



//END
