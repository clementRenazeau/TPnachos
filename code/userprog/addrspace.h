// addrspace.h 
//      Data structures to keep track of executing user programs 
//      (address spaces).
//
//      For now, we don't keep any information about address spaces.
//      The user level CPU state is saved and restored in the thread
//      executing the user program (see thread.h).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef ADDRSPACE_H
#define ADDRSPACE_H

#include "copyright.h"
#include "filesys.h"
#include "translate.h"
#include "bitmap.h"

#define UserStacksAreaSize		1024*8	// increase this as necessary!

#ifdef CHANGED
class Semaphore;
#endif //CHANGED
class AddrSpace:dontcopythis
{
  public:
    AddrSpace (OpenFile * executable);	// Create an address space,
    // initializing it with the program
    // stored in the file "executable"
    ~AddrSpace ();		// De-allocate an address space

    void InitRegisters ();	// Initialize user-level CPU registers,
    // before jumping to user code

    void SaveState ();		// Save/restore address space-specific
    void RestoreState ();	// info on a context switch 

#ifdef CHANGED
    int AllocateUserStack();
    void DeAllocateUserStack(int stack);
    void IncThreads();
    void DecThreads();
    unsigned int GetNbThreads();
    void WaitLastThread();
    static unsigned int GetNbAddrSpaces();
#endif // CHANGED

  private:
      TranslationEntry * pageTable;	// Assume linear page table translation
    // for now!
    unsigned int numPages;	// Number of pages in the virtual
    static unsigned int nbAddrSpaces;
    // address space
#ifdef CHANGED
    unsigned int numThreads;
    Semaphore *mutexThreads;
    Semaphore *semaphoreMain;
    BitMap *userStacks;
#endif //CHANGED
};

#endif // ADDRSPACE_H
