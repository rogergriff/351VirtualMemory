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

#include "HARDWARE.h"
#include "OS.h"

#define FRAME_SIZE 256 			//size of the frame
#define TOTAL_NUMBER_FRAMES 256 	// total number of frames in physical memory


/********** MAIN *********/
int main()
{ 	
	int aSize = 0;			//?
	
	//int size = 999;		//DELETE
	//vector<uint32_t> a(size);	//DELETE
	//Word page;  			//DELETE 
		
	Word offset;			//name for the offset thatwill be obtained
	
	//uint32_t a;			//DELETE
	//int page;  			//DELETE
	//int offset;			//DELETE	
	
	//variables to accesses classes and structs
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
			if (myfile.eof())		//?
			{
				break;
			}

			else if(!myfile.eof())		//?
			{
				//a[aSize] = x;
				aSize++;		//?
			}
		
			else
			{
				cout <<"error reading in addresses"; 			//output error, shouldn't eer reach this point
			}
			
			page_table_number = add.page(x);				//gets the number to use for the page table
			page_table_number.u_int = page_table_number.u_int>>8; 		//shifting the result we got so that its an appropriate page number
			offset = add.offset(x);						//gets the offset to use for the frame
			o = offset.u_int;
			
			if(unit.inTLB(page_table_number.u_int)) 		//If found in TLB continue with the following instructions
			{
				unit.addTLBAccesses();					//add to TLB access count
				frame = unit.readTLBTable(page_table_number.u_int);	//use the frame number to take the info from the frame table
			}
				
			else							//If not found in the TLB, look for it in the page table
			{
				unit.addTLBFaults();							//add to TLB fault count
				//cout << "no seg fault after tlb missed\n"; 				//DELETE
				e = memory.readPageTable(page_table_number.u_int, unit, ram, b);	//Reads the page table
				unit.Replace(e);							//Replace the tlb if page not found
				//cout << "didn't find e in tlb table, did replace, returning " << e.frameNumber << endl;	
				frame = e.frameNumber;		
			}
			
			unsigned char m = ram.read(frame,o);						//?
			//m << hex << m;								//DELETE
			cout << e.pageNumber << "\t\t" << e.frameNumber << "\t\t" << m << endl;		//prints out page corresponding page num and frame num
			//cout << hex << m << endl;							//DELETE
		}
		
		cout << "page faults is " << unit.pageFaults() << "\t aSize is " << aSize << endl;		//prints out page fault and the page at which it occured
		page_fault_rate = (static_cast<float> (unit.pageFaults())/static_cast<float> (aSize)) * 100;	//calculte page fault rte
		cout << "\n\n\n\n\n\n\nThe page fault rate was:" << page_fault_rate << "%\n";// << (unit.pageFaults()/aSize) * percent<<"%\n"; //prints out rate

		tlb_hit_rate = (static_cast<float> (unit.TLBAccesses())/static_cast<float> (aSize)) * 100; 	//calcuates TLB hit rate
		cout << "The TLB Hit rate was:" << tlb_hit_rate << "%\n";					//printsout TLB rate
	}
	
	myfile.close();		//closes file
	output.close();		//?
	return 0;	

}

/********** END OF MAIN **********/



/********** UINT32_t - HARDWARE **********/
int Word::uin32_t(uint32_t x)
{
	u_int = static_cast<int> (x);	//?
	return x;			//
}

/********** PAGE - HARDWARE **********/
Word address::page(uint32_t a)
{
	Word p;
	p.u_int = p.uin32_t(a & 65280); 	//bit masking so that we get only get page bits 15 through 8
	return p;
}

/********** OFFSET - HARDWARE **********/
Word address::offset(uint32_t a)
{
	Word o;
	o.u_int = o.uin32_t(a & 255);		//bit masking to get offset bits 0 to 7
	return o;
}

  
/*
//OS header functions		//DELETE
PRA::~PRA();
*/
  
/*
Word PRA::findVictim (){		//DELETE
  
};
*/
  
/*
Word PRA::getPRA (){		//DELETE
  
}; 
*/
  
/*
Word PRA::updateUsage(){	//DELETE
  
};
*/
  


/********** MEMORY MANAGER - 0S **********/
MM::MM(){
PCB block;
	//for(int i=0; i <256; ++i){ //code for debugging
	//cout << "for block.myPageTable[" << i << "].frameNumber we have a value of:" << block.myPageTable[i].frameNumber << endl;
	//cout << "for block.myPageTagle[" << i << "].valid we have a value of :" << block.myPageTable[i].valid << endl;
}

  
/*
MM MM::instance(){
};
*/
    
/*
bool MM::operator=(){
};
*/


/********** READ PAGE TABLE **********/
//shouldn't this be in MMU not MM
tlbEntry MM::readPageTable(int x, MemoryManagementUnit& u, RAM& r, BackingStore& b)
{
	tlbEntry e;		//uses hardware- tlb entry from MMU is set
	if(pageTable.myPageTable[x].valid == true)	//if the page number is valid in the table then continue
	{
		//cout<< "found entry for page " << x <<  "and it was " << pageTable.myPageTable[x].frameNumber << endl;	//DELETE
		u.addPageAccesses();					//page accesses count is incremented
		e.frameNumber = pageTable.myPageTable[x].frameNumber;	//?
		e.pageNumber = x;					//?
		return e;						//
	}

	else if(pageTable.myPageTable[x].valid == false)	//is page number not valid in the table then continue with the following
	{
		//cout << "failed to find page " << x << ", using page in \n";	
		u.addPageFaults();					//add page fault
		//cout << "no seg fault before readPageTable\n";	//DELETE
		pageIn(pageTable.myPageTable, x, r,b);			//?
		return readPageTable(x,u,r,b);				//returns page table
	}
	//else						//DELETE
	//cout << "error reading page table"<< endl;	//DELETE
	return e;					

} 
 


/********** PAGE IN - OS **********/
void MM::pageIn(PTE pageT[], int page, RAM& r,BackingStore& backing)
{
	//pageT[page].frameNumber= freeFrames();		//DELETE
	//cout << "no seg fault before pageIn\n";		//DELETE
	pageT[page].frameNumber = r.FreeFrames(page,backing);	//?
	//cout << "went into page in and set frame number to " << pageT[page].frameNumber << "for page " << page << endl;	//DELETE
	pageT[page].valid = true;				//?
	//cout << "set page " << page << "'s frame number to " << pageT[page].frameNumber << endl;	//DELETE
	//cout << "went into page in and set valid for "<< page << endl;				//DELETE
}
           


/********** MEMEORY MANAGEMENT UNIT CONSTRUCTOR - HARDWARE**********/
MemoryManagementUnit::MemoryManagementUnit(){
	Page_AccCount = 0;		//initialize page access count to 0
	Page_Faults = 0;		//initializes page fault count to 0
	//TLB_AccCount = 0;		//DELETE
	//TLB_Faults = 0;		//DELETE
	clearTLB();			//clears TLB
}


/********** IN TLB - HARDWARE **********/
//?
bool MemoryManagementUnit::inTLB(int x)		//?
{
	for(int i = 0; i < 16; ++i)
	{
		if(tBuffer[i].pageNumber == x)		//?
		return true;				//?
	}
	
	return false;
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
			//cout << "found page " << x << " in tlb table, returning " << e.frameNumber << endl;
			updateUsageLRU(e);  //comment out this line to change from LRU to FIFO
			return e.frameNumber;			
		}
/*	
	}
	e = m.readPageTable(x,r,u);
	Replace(e);
	cout << "didn't find e in tlb table, did replace, returning " << e.frameNumber << endl;	
*/	
	}
	return 0;
}


/********** UPDATE USAGE LRU - HARDWARE **********/
//TLB replacement algorithms - LRU
void MemoryManagementUnit::updateUsageLRU(tlbEntry x)
{
	for(int i = x.pageNumber; i<15; ++i)
	{
		tBuffer[i].pageNumber = tBuffer[i+1].pageNumber;	//?
		tBuffer[i].frameNumber = tBuffer[i+1].frameNumber;	//?
	}
	tBuffer[15] = x;
}
  

/********** REPLACE - HARDWARE **********/
//TLB replcement algorithm - FIFO
void MemoryManagementUnit::Replace(tlbEntry e)
{
	for(int i = 0; i < 15; i++)
	{
		tBuffer[i] = tBuffer[i+1];	//?
	}
	
	tBuffer[15] = e;
	//cout << "putting page " << e.pageNumber << " which is frame " << e.frameNumber << "at the end of tlb table.\n";	//DELETE
}


/********** CLEAR TLB **********/
//clears TLB entries
void MemoryManagementUnit::clearTLB()
{
	for(int i = 0; i < 16; ++i)
	{
		tBuffer[i].pageNumber = -1;	//?
		tBuffer[i].frameNumber = -1;	//?
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


/*
BackingStore BackingStore::instance()		//DELETE
{
}
*/
/*
bool BackingStore :: opertor=()			//DELETE
{
}
*/


/********** READ - HARWARE **********/
//reads from the backing_store.bin file
void BackingStore :: read(int p, Frame fT[256])	
{
	//if reading a frame at a time			//DELETE
	//x= read from backing store code		//DELETE
	//fT[p] = x;					//DELETE
	//if can't read frame at a time			//DELETE
	//fT[p].fillFrame();				//DELETE
	//in fill frame, do a for loop that will fill in the individual bits as they are read out.	//DELETE
	//cout << "got into backingstore read\n";	//DELETE
	//unsigned char x;// = fT[p].readFrame();	//DELETE
	//cout << "got a value in for x\n";		//DELETE
	
	int y = p*256;						//?
	
	//cout << "got a value in for y\n";		//DELETE
	//ifstream file ("BACKING_STORE.bin", ios::in|ios::binary|ios::ate);	//DELETE
	
	ifstream file;						//?
	file.open("BACKING_STORE.bin", ios::in|ios::binary);	//Opens binary file
	
	//cout << "opened the .bin file\n";			//DELETE
	
	if(file.is_open())					//????????? should this need curly brackets?
		file.seekg(y);					//seeks bin file
		char * buffer = new char [256];			//??
		unsigned char * buff = new unsigned char [256];	//?
		file.read(buffer,256);				//reads ???
	
	//memcpy( &x, &y, 255);				//DELETE
	//cout << "did memcpy\n";			//DELETE
	
	buff = reinterpret_cast<unsigned char*> (buffer);	//converts signed chars to unsigned char
	fT[p].fillFrame(buff);					//?
	
	//cout << "ft[p].fillframe did its work.\n";	//DELETE
	
	file.close();					//closes binary file
	
	//cout << "file closed.\n";			//DELETE

}




/********** RAM - HARDWARE **********/
//Ram
RAM::RAM()
{
	for(int i = 0; i<256; ++i)
	{
		arrStatus[i].frameNumber = i;		//sets status for frame number i
		//cout << "created a frame # " << arrStatus[i].frameNumber << "\taccessed is " << arrStatus[i].accessed << "\tdirty is " << arrStatus[i].dirty << endl;
	}
	
	//cout << "created a ram ";			//DELETE
	//for(int i = 0; i < frameSize; ++i)		//DELETE
	//cout << "frame " << i << " created and has value of " << framesTable[i].data << endl;		//DELETE
}


/*
RAM RAM::instance()				//DELETE
{
}
*/
/*
//bool operator=();				//DELETE
Bool RAM::operator=()				//DELETE
{
}
*/



/********** READ - HARDWARE **********/
unsigned char RAM::read(int f, int o)
{
	return framesTable[f].readFrame(o);	//returns 
}



/********** READ FRAME - HARDWARE **********/
unsigned char Frame:: readFrame(int o)
{
	//cout << "entered into readFrame\n";	
	//for (int i = 0; i < 256; ++i)
	return data[o];				//return
	return 0;				//return
}



/********** FREE FRAMES - HARDWRAE **********/
//Uses hardware to inform if the frame is dirty ??????
int RAM::FreeFrames(int p, BackingStore b) 
{
	for (int i = 0; i < 256; ++i)
	{
		if(arrStatus[i].dirty == true)	
		{	
			//cout << "no seg fault before freeFrames\n";			//DELETE
			b.read(p, framesTable);					//reads 
			//cout << "returned from backing store read\n";			//DELETE
			arrStatus[i].dirty = false;				//???
			//cout << "set the dirty bit to false\n";			//DELETE
			arrStatus[i].accessed = false;				//???
			//cout << "set the accessed to false\n"; 			//DELETE
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
