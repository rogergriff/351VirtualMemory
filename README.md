# 351VirtualMemory
We currently have a page table that links to the frames table, an empty frames table, and still have the code for the statistics commented out.

We still need to:
Find a way to populate the frames table.
  probably do it similar to how we fill up the page table and just do it on demand
  
Find a way to get the .bin into the program so that we can access it whenever
  i'm assuming we're just gonna put it into the backing store class and keep it there so we only have to open the file once     and just read it in once.

Get the info from that place we put the .bin into the frames table
  Framestable is an array of type frame, so we just have to pull the data a frame at a time and populate the frames table.
 
Implement the TLB and its PRAs
  An array of size 16 would proably be fine, then we just have to implement the PRAs. For fifo, i think we can just do something like a for loop that sets TLB[0] = TLB[1] and increments the numbers all the way to TLB[TLB_size -1] = TLB[TLB_size] then sets TLB[TLB_size] = the new thing. Probably do a struct for TLB Entry that has page number and frame number as ints and use that as the type for the array.  

  
  
  
Make sure you have all the cpp and both .h files, as well as the .txt
Commands to do in linux terminal:
g++ -g3 -O0 -std=c++17 -pedantic -Wall -Wold-stle-cast -Wextra -Woverloaded-virtual -I./ -o VMManager hw.cpp HARDWARE.h OS.h 

./VMManager <addresses.txt 2)&1 | tee output.txt




