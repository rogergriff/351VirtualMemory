//header file for the hardware portion
class HW{
};

class MMU: public HW{ //Memory Management Unit
private:
  int page_acc_count;
  int page_faults;
  tlb; //The actual tlb i think
  int tlb_acc_count; //how many times accessed
  int tlb_faults; //how many faults
public:
  void clearTLB(); // clears the TLB
  instance(); // ??? no idea what it does, but its on the hints, maybe creates tlb?
  MMU(); // constructor
  void pageAccesses(); //how many pages were accessed? pretty sure a simple cout
  void pageFaults(); //how many page faults where there? pretty sure a simple cout
  read<T>;//read from standard input the 32 bit integer numbers that represent logical addresses 
  tlbAccesses(); //how many times did the TLB get accessed? pretty sure just a simple cout
  tlbFaults(); //how many times was there a fault accessing?  ^
}

class PageFault: public MMU{ 
public:
  PageFault();
  Word pageNumber;
};
struct Word: public HW{
  int uint32_t(); // make the value i think?
  uint32_t value;
};

struct Adr: public Word{ //Address
Word Adr(); //implement it
Word displacement();
Word frame();
Word page();  //
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
