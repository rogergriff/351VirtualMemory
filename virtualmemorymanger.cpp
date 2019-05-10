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
	MemoryManagementUnit unit;
	RAM ram;
	float page_fault_rate;

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
			
			else if(!myfile.eof())
			{
				a[aSize] = x;
				aSize++;
			}
			
			else
			{
				cout <<"error reading in addresses"; //should never get here, seeing how you should only ever find the eof, or find that its not eof
			 }
			
		}
/*
		for (int i = 0; i < aSize; i++){
		cout<< a[i] <<" " <<endl;}
*/
		//cout << "aSize is " << aSize << endl;		
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
			memory.readPageTable(page_table_number.u_int, unit,ram);
		}

		cout << "page faults is " << unit.pageFaults() << "\t aSize is " << aSize << endl; 
		page_fault_rate = (static_cast<float> (unit.pageFaults())/static_cast<float> (aSize)) * 100;
		cout << "\n\n\n\n\n\n\nThe page fault rate was:" << page_fault_rate << "%\n";// << (unit.pageFaults()/aSize) * percent<<"%\n";
		//cout<< "The amount of TLB hit rate was:" << (unit.TLB_Accesses()/aSize)*100<<"%\n";
		return 0;
	}
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

/* 	a "Word" type will be created
	
*/
	
//tlb

//go into page table array, page 0 to page 255
// processControlBlock struct will contain the page table
/*	if there then we get a frame number
	{
	
	}
	if not available == Page Fault{
		- Backingstore.bin will be used if there is a page fault
		- backingstore.bin is size 256
		- Ex: if we need pg.15 but it resulted in  page fault, in order to find it from the bin
			we can use 256 * 15 to find the beginning of the corresponding frame number
	}
	
*/
		
//Frame number is allocated
	
//Go to required frame
//While in frame, use offset to go to the beginning of a specific line
	

//read out whatever is in that specific frame
	
	
//}
  
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
MM MM::instance(){
};
*/
    
/*
bool MM::operator=(){
};
*/
    
int MM::readPageTable(int x, MemoryManagementUnit& u,RAM& r)
{
	if(pageTable.myPageTable[x].valid == true)
	{
		//cout<< "found entry for page " << x <<  "and it was " << pageTable.myPageTable[x].frameNumber << endl;
		u.addPageAccesses();	
		return pageTable.myPageTable[x].frameNumber;
	}
	
	else if(pageTable.myPageTable[x].valid == false)
	{
		//cout << "failed to find page " << x << ", using page in \n";	
		u.addPageFaults();	
		pageIn(pageTable.myPageTable, x, r);
		return readPageTable(x,u,r);
	}
/*else
	cout << "error reading page table"<< endl;*/
	return 0;

}  

void MM::pageIn(PTE pageT[], int page, RAM& r)
{
	//pageT[page].frameNumber= freeFrames();
	pageT[page].frameNumber = r.checkArrStatusforDirty();
	cout << "went into page in and set frame number to " << pageT[page].frameNumber << "for page " << page << endl;
	pageT[page].valid = true;
	//cout << "set page " << page << "'s frame number to " << pageT[page].frameNumber << endl;
	//cout << "went into page in and set valid for "<< page << endl;
}
  
           


 //class Memory Management Unit
//begin
//default constructor

MemoryManagementUnit::MemoryManagementUnit()
{
	Page_AccCount = 0;
	Page_Faults = 0;
	//TLB_AccCount = 0;
	//TLB_Faults = 0;
}



/* TLB

int MemoryManagementUnit::readTLBtable(int x, Ram& r)
{
	if(TLBtable.myTLBtable[x].valid == true)
	{
		addTLBaccess();
		return TLBtable.myTLBtable[x].frameNumber;
	}
	
	else if(TLBtbale.myTLBtable[x].valid == false)
	{
		addTLBfaults();
		pageIn(TLBtable.myTLBtable, x, r);
		return readTLBtable(x, r);
	}
	
	return 0;
}

*/




//
int MemoryManagementUnit::pageAccesses()
{
	return Page_AccCount;
}


int MemoryManagementUnit::pageFaults()
{
	return Page_Faults;
}

void MemoryManagementUnit::addPageAccesses(
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
int MemoryManagementUnit:: TLB_Faults()
{
	return TLB_Faults;	//counts how many tlb faults
}
*/

	
	
/*
void MemoryManagementUnit::addTLBaccess()
{
	++TLB_AccCount;
}
*/
	
	
/*
void MemoryMangementUnit::addTLBfaults()
{
	++TLB_Faults;
}
*/
 
 
 
/* 
In hardware.h it should be:
bool operator=( const MemoryManagementUnit& ) const;
*/
	
	
/*
bool MemoryManagementUnit:: operator=( const MemoryManagementUnit & a ) const
{
	
}
//end of Memory Management Unit
*/


//word

backing store
BackingStore::BackingStore()
{
 streampos size;
  char * info;

  ifstream file ("BACKING_STORE.bin", ios::in|ios::binary|ios::ate);
  if (file.is_open())
  {
    size = file.tellg();
    info = new char [size];
    file.seekg (0, ios::beg);
    file.read (info, size);
    file.close();

    cout << "all file content is in memory";

    delete[] info;
  }
  else cout << "Cannot Open backing store file";
  return 0;

}

	
	
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


//Ram
RAM::RAM()
{
	for(int i = 0; i<256; ++i)
	{
		arrStatus[i].frameNumber = i;
		cout << "created a frame # " << arrStatus[i].frameNumber << "\taccessed is " << arrStatus[i].accessed << "\tdirty is " << arrStatus[i].dirty << endl;
	}
	//cout << "created a ram ";
	//for(int i = 0; i < frameSize; ++i)
	//cout << "frame " << i << " created and has value of " << framesTable[i].data << endl;
}


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

int RAM::checkArrStatusforDirty()
{
	for (int i = 0; i < 256; ++i)
	{
		if(arrStatus[i].dirty == true)
		{
			arrStatus[i].dirty = false;
			arrStatus[i].accessed = false;
			return i;
		}
	}	
return 0;
}
