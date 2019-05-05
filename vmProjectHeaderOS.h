#ifndef OS_H
#define OS_H
#include <iostream>
#include <fstream>
using namespace std;

/*
//this will be the header file for the OS part our project
class OS{

}; */

class PRA{ //Page replacement algorithm
      struct FIFO {
        public:
           Word findVictim();
           FIFO(); // constructor
        private:
           Word front; // what's at the front and will therefore be booted next when it's full.
      }; 
      class LRU {
         public:
           Word findVictim();
           LRU();
           void updateUsage();
        private:
           LRUList;
       }
        
    private:
          int options(); //use this to get the type of PRA wanted at run-time, so something like "what page replacemnt algorithm do you want to use, 1 for fifo or 2 for lru
    protected:
          PRA(); //constructor for class
    public:
          ~PRA(); //destructor
           Word findVictim();
           getPRA();
           updateUsage();
  };


/* struct FIFO: public PRA{
public:
  Word findVictim();
  FIFO(); //constructor 
  
private:
  Word front; //what's at the front and will therefore be booted next when it's full.
};
*/

/*struct LRU: public PRA{
public:
  Word findVictim();
  LRU();
  void updateUsage();
  
private:
  LRUList;
};
*/

class MM{ //Memory Manager for OS
     private:
        freeFrames(); //which frames are free, if any??
        MM(); //constructor??
        PCB pageTable;
     public:
        MM(); //constructor creates pcb
        instance();//?
        operator=();//?
        void pageIn(pageTable); //bring in page via demand paging, see 10.2 in book
 };

struct PTE{ //Page Table Entry
  unsigned char frameNumber;
  bool valid;
};

struct PCB{ //Process control block
  PTE myPageTable[256];
};

#endif
