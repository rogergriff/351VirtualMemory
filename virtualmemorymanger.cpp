#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <iomanip>
#define FRAME_SIZE 256 // size of the frame
#define TOTAL_NUMBER_FRAMES 256 // total number of frames in physical memory
using namespace std;

#include "HARDWARE.h"
#include "OS.h"


int main()
{ 	
	int aSize = 0;
	
	//int size = 999;	
	//vector<uint32_t> a(size);
	//Word page;  //delete before turning in if the program works
		
	Word offset;
	
	//uint32_t a;
	//int page;  //delete before turning in
	//int offset;	//delete before turning in	
		
	Word page_table_number;
	address add;
	MM memory;
	MemoryManagementUnit unit;
	RAM ram;
	float page_fault_rate;
	float tlb_hit_rate;
	int frame;
	int o;
	tlbEntry e;
	BackingStore b;
	cout << "Logical Address \tPhysical Address \tUnsigned Byte Value\n";
    	ifstream myfile("addresses.txt");
	ofstream output("output.txt");
	
	if(myfile.is_open())
	{	
		while(true)
		{
			uint32_t x;
			myfile >> x;
			if (myfile.eof())
				{
					break;
				}

				else if(!myfile.eof())
				{
		//			a[aSize] = x;
					aSize++;
				}
		

				else
				{
				cout <<"error reading in addresses"; //should never get here, seeing how you should only ever find the eof, or find that its not eof
				}
				
			

	
		
			page_table_number = add.page(x); //gets the number to use for the page table
			page_table_number.u_int = page_table_number.u_int>>8; //shifting the result we got so that its an appropriate page number
			offset = add.offset(x); //get the offset to use for the frame
			o = offset.u_int;
			
			if(unit.inTLB(page_table_number.u_int)) //If we find it in the TLB, we can take the frame number directly and read the info from the frames table
			{
				unit.addTLBAccesses();
				frame = unit.readTLBTable(page_table_number.u_int);
			}
			else //If we didn't find it in the TLB, we see if its in the page table. If it is, we 
			{
				unit.addTLBFaults();
				//cout << "no seg fault after tlb missed\n"; 
				e = memory.readPageTable(page_table_number.u_int, unit, ram, b);
				unit.Replace(e);
				//cout << "didn't find e in tlb table, did replace, returning " << e.frameNumber << endl;	
				frame = e.frameNumber;		
			}
		unsigned char m = ram.read(frame,o);
		//m << hex << m;
		cout << e.pageNumber << "\t\t" << e.frameNumber << "\t\t" << m << endl;
		//cout << hex << m << endl;	
			
		
}
cout << "page faults is " << unit.pageFaults() << "\t aSize is " << aSize << endl; 
page_fault_rate = (static_cast<float> (unit.pageFaults())/static_cast<float> (aSize)) * 100;
cout << "\n\n\n\n\n\n\nThe page fault rate was:" << page_fault_rate << "%\n";// << (unit.pageFaults()/aSize) * percent<<"%\n";
tlb_hit_rate = (static_cast<float> (unit.TLBAccesses())/static_cast<float> (aSize)) * 100;
cout << "The TLB Hit rate was:" << tlb_hit_rate << "%\n";


}
myfile.close();
output.close();
return 0;

}






int Word::uin32_t(uint32_t x){
u_int = static_cast<int> (x);
return x;
}

Word address::page(uint32_t a){
Word p;
p.u_int = p.uin32_t(a & 65280); //bit masking so that we get only bits 15 through 8
return p;
}

Word address::offset(uint32_t a){
Word o;
o.u_int = o.uin32_t(a & 255);
return o;
}

  
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
  

//From class LRU:public PRA
    


//From Class Memory Manager  
    
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
    
tlbEntry MM::readPageTable(int x, MemoryManagementUnit& u, RAM& r, BackingStore& b)
{
tlbEntry e;
if(pageTable.myPageTable[x].valid == true){
	//cout<< "found entry for page " << x <<  "and it was " << pageTable.myPageTable[x].frameNumber << endl;
	u.addPageAccesses();	
	e.frameNumber = pageTable.myPageTable[x].frameNumber;
	e.pageNumber = x;
	return e;
}
else if(pageTable.myPageTable[x].valid == false){
	//cout << "failed to find page " << x << ", using page in \n";	
	u.addPageFaults();
//	cout << "no seg fault before readPageTable\n";	
	pageIn(pageTable.myPageTable, x, r,b);
	return readPageTable(x,u,r,b);
}
/*else
	cout << "error reading page table"<< endl;*/
	return e;

} 
 

void MM::pageIn(PTE pageT[], int page, RAM& r,BackingStore& backing){
//pageT[page].frameNumber= freeFrames();
//cout << "no seg fault before pageIn\n";
pageT[page].frameNumber = r.FreeFrames(page,backing);
//cout << "went into page in and set frame number to " << pageT[page].frameNumber << "for page " << page << endl;
pageT[page].valid = true;
//cout << "set page " << page << "'s frame number to " << pageT[page].frameNumber << endl;
//cout << "went into page in and set valid for "<< page << endl;

}
           


 //class Memory Management Unit
//begin
//default constructor

MemoryManagementUnit::MemoryManagementUnit(){
	Page_AccCount = 0;
	Page_Faults = 0;
	//TLB_AccCount = 0;
	//TLB_Faults = 0;
	clearTLB();
}


bool MemoryManagementUnit::inTLB(int x){
for(int i = 0; i < 16; ++i)
	{
		if(tBuffer[i].pageNumber == x)
			return true;				
	}
	return false;
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

void MemoryManagementUnit::addPageAccesses(){
++Page_AccCount;
}

void MemoryManagementUnit::addPageFaults(){
++Page_Faults;
}


int MemoryManagementUnit:: TLBAccesses()
{
	return TLB_AccCount;	
}



void MemoryManagementUnit:: addTLBAccesses()
{
	++TLB_AccCount;
	
}



int MemoryManagementUnit:: TLBFaults()
{
	return TLB_Faults;//counts how many tlb faults
}


void MemoryManagementUnit::addTLBFaults()
{
	++TLB_Faults;
} 
//In hardware.h it should be:
//bool operator=( const MemoryManagementUnit& ) const;
/*
bool MemoryManagementUnit:: operator=( const MemoryManagementUnit & a ) const
{
	
}
*/

//TLB
//int MemoryManagementUnit::readTLBtable(int x, Ram& r)
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

void MemoryManagementUnit::updateUsageLRU(tlbEntry x){
for(int i = x.pageNumber; i<15; ++i)
{
	tBuffer[i].pageNumber = tBuffer[i+1].pageNumber;
	tBuffer[i].frameNumber = tBuffer[i+1].frameNumber;
}
tBuffer[15] = x;
	
}
  

void MemoryManagementUnit::Replace(tlbEntry e){
	for(int i = 0; i < 15; i++){
	tBuffer[i] = tBuffer[i+1];
}
tBuffer[15] = e;
//cout << "putting page " << e.pageNumber << " which is frame " << e.frameNumber << "at the end of tlb table.\n";
}

void MemoryManagementUnit::clearTLB(){
for(int i = 0; i < 16; ++i)
{
	tBuffer[i].pageNumber = -1;
	tBuffer[i].frameNumber = -1;	
}
}
//end of Memory Management Unit




//backing store
BackingStore::BackingStore()
{


}


BackingStore:: ~BackingStore()
{
}

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

void BackingStore :: read(int p, Frame fT[256])
{
	//if reading a frame at a time
	
	//x= read from backing store code
	//fT[p] = x;

	//if can't read frame at a time
	
	//fT[p].fillFrame();
	//in fill frame, do a for loop that will fill in the individual bits as they are read out.
//	cout << "got into backingstore read\n";	
	//unsigned char x;// = fT[p].readFrame();
//	cout << "got a value in for x\n";
	int y = p*256;
//	cout << "got a value in for y\n";	
	//ifstream file ("BACKING_STORE.bin", ios::in|ios::binary|ios::ate);
	ifstream file;	
	file.open("BACKING_STORE.bin", ios::in|ios::binary);
//	cout << "opened the .bin file\n";	
	if(file.is_open())
		file.seekg(y);
	char * buffer = new char [256];
	unsigned char * buff = new unsigned char [256];
		file.read(buffer,256);
//	memcpy( &x, &y, 255);
//	cout << "did memcpy\n";
	buff = reinterpret_cast<unsigned char*> (buffer);
	fT[p].fillFrame(buff);
//	cout << "ft[p].fillframe did its work.\n";
	file.close();
//	cout << "file closed.\n";
//	
}



//Ram
RAM::RAM(){
for(int i = 0; i<256; ++i){
	arrStatus[i].frameNumber = i;
	//cout << "created a frame # " << arrStatus[i].frameNumber << "\taccessed is " << arrStatus[i].accessed << "\tdirty is " << arrStatus[i].dirty << endl;
}
	//cout << "created a ram ";
	//	for(int i = 0; i < frameSize; ++i)
	//		cout << "frame " << i << " created and has value of " << framesTable[i].data << endl;
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

//idk if this is correct
unsigned char RAM::read(int f, int o)
{
return framesTable[f].readFrame(o);
}

unsigned char Frame:: readFrame(int o){
	//cout << "entered into readFrame\n";	
	//for (int i = 0; i < 256; ++i)
		 return data[o];
return 0;
}

int RAM::FreeFrames(int p, BackingStore b) //tells us which frame is dirty, this is used to 
{
	for (int i = 0; i < 256; ++i){
		if(arrStatus[i].dirty == true)
		{	
			//cout << "no seg fault before freeFrames\n";
			b.read(p, framesTable);
			//cout << "returned from backing store read\n";
			arrStatus[i].dirty = false;
			//cout << "set the dirty bit to false\n";
			arrStatus[i].accessed = false;
			//cout << "set the accessed to false\n"; 
			return i;
		}
}	

return 0;
}

void Frame::fillFrame(unsigned char x[]){
for(int i = 0; i<256; ++i){
	data[i] = x[i];
}
}
