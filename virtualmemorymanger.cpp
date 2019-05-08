#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "HARDWARE.h"
#include "OS.h"








int main() { 
  
		int aSize = 0;
		int size = 999;
		
		vector<uint32_t> a(size);
		//Word page;
		Word offset;
		//int page;
		//int offset;		
		Word page_table_number;
		address add;
		MM memory;

    ifstream myfile("addresses.txt");
	if(myfile.is_open()){
		

		while(true){
			uint32_t x;
			myfile >> x;
			if (myfile.eof()){
			cout << "breaking out after aSize=" << aSize << " because found eof.\n"; 
			break;
}
			else if(!myfile.eof()){
			a[aSize] = x;
			aSize++;

			}
		

			else{
				cout <<"error reading in addresses";
			    }
				
				}/*
for (int i = 0; i < aSize; i++){
				cout<< a[i] <<" " <<endl;}
*/
//cout << "aSize is " << aSize << endl;		
myfile.close();
/* dont know if this is how we're supposed to do this but this theoretical masks the bits to get the page and the offset. 
Then it shifts it by 8 to get the page table number. */	
		for (int i=0; i< aSize; i++) {
			//page = 
			//offset = 
			page_table_number = add.page(i,a); //gets the number to use for the page table
			//cout << "got " << page_table_number.u_int << " from add.page(i,a) \t";
			//cout << "the vector looks like this: \n";
			//	for(int i=0; i<aSize; ++i)
			//		cout << a[i] << endl;
			page_table_number.u_int = page_table_number.u_int>>8;
			offset = add.offset(i,a); //get the to use for the frame
//cout << page << endl;
			//cout << "page table number:" << page_table_number.u_int <<"\toffset:"<< offset.u_int<< endl;
			
			
}



return 0;

}}


int Word::uin32_t(uint32_t x){
u_int = static_cast<int> (x);
return x;
}

Word address::page(int x, vector<uint32_t> a){
Word p;
p.u_int = p.uin32_t(a[x] & 65280);
return p;
}

Word address::offset(int x, vector<uint32_t> a){
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
    
MM::MM(){
PCB block;
	//for(int i=0; i <256; ++i){
	//cout << "for block.myPageTable[" << i << "].frameNumber we have a value of:" << block.myPageTable[i].frameNumber << endl;
	//cout << "for block.myPageTagle[" << i << "].valid we have a value of :" << block.myPageTable[i].valid << endl;
}
}
  
/*
MM MM::instance(){
};
*/
    
/*
bool MM::operator=(){
};
*/
    
/*
void MM::pageIN(pageTable){



};
  */
  
           



//Header HARDWARE
  
/*  
 //class Memory Management Unit
//begin
//default constructor 
MemoryManagementUnit : MemoryManagementUnit()
{
	Page_AccCount = 0;
	Page_Faults = 0;
	TLB_AccCount = 0;
	TLB_Faults = 0;
}
*/

/*
//
int MemoryManagementUnit:: pageAccesses()
{
	
}
*/
/*
int MemoryManagementUnit:: pageFaults()
{
	
}
*/

/*
int MemoryManagementUnit:: TLB_Accesses()
{
	
}
*/

/*
int MemoryManagementUnit:: TLB_Accesses()
{
	//
	
}
*/

/*
int MemoryManagementUnit:: TLB_Faults()
{
	//counts how many tlb faults
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
