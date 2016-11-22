#include "thread.h"
#include "machine.h"
#include "system.h"

#ifdef USER_PROGRAM
static void StartUserThread(void *schmurtz);
struct ThreadParameters {
  int function;
  int argument;
  int stack;
  int exitAddress;
};

int do_createThread(int f, int arg, int exitAddress) {
  int stack = currentThread->space->AllocateUserStack();
  if(stack != -1){
    Thread *newThread = new Thread("userThread");
    ThreadParameters *p = new ThreadParameters {f, arg, stack, exitAddress};
    newThread->space->IncThreads();
    newThread->userStackTop = stack;
    newThread->Start(StartUserThread, p);
    return 0;
  }
  return -1;
}

void StartUserThread(void *schmurtz) {
  ThreadParameters *p = static_cast<ThreadParameters*>(schmurtz);
  for (int i = 0; i < NumTotalRegs; i++) {
    machine->WriteRegister (i, 0);
  }

  machine->WriteRegister (PCReg, p->function);
  machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);
  machine->WriteRegister (4, p->argument);
  machine->WriteRegister (StackReg, p->stack);
  machine->WriteRegister (31, p->exitAddress);
  DEBUG ('a', "Initializing stack register to 0x%x\n",p->stack);
  delete p;
  machine->Run();
}

void do_ThreadExit(){
  currentThread->space->DeAllocateUserStack(currentThread->userStackTop);
  currentThread->space->DecThreads();
  currentThread->Finish();
}

void StartForkExec(void *schmurtz){
  currentThread->space->InitRegisters ();
  currentThread->space->RestoreState ();
  machine->Run();
}

int do_ForkExec(const char* s){
  OpenFile *executable = fileSystem->Open (s);
  AddrSpace *space;

  if (executable == NULL){
      printf ("Unable to open file %s\n", s);
      return -1;
    }
  space = new AddrSpace (executable);
  Thread *threadNoyau = new Thread("ForkMain");
  threadNoyau->space = space;
  delete executable;
  threadNoyau->Start(StartForkExec, NULL);
  return 0;
}
#endif
