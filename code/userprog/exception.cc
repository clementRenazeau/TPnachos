// exception.cc 
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.  
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#ifdef CHANGED
#include <algorithm>
#include "sysutils.h"
#include "userthread.h"
#endif
//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void
UpdatePC ()
{
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}


//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions 
//      are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler (ExceptionType which)
{
  int type = machine->ReadRegister (2);

  switch (which)
    {
    case SyscallException:
      {
	switch (type)
	  {
	  case SC_Halt:
	    {
	      DEBUG ('s', "Shutdown, initiated by user program.\n");
	      interrupt->Halt ();
	      break;
	    }
#ifdef CHANGED
	  case SC_Exit:
	    {
	      DEBUG ('s', "Shutdown, initiated by user program.\n");
	      int returnValue = machine->ReadRegister(4);
	      if(currentThread->space->GetNbThreads() > 0) {
		currentThread->space->WaitLastThread();
	      }
	      printf("\nExited with code %d\n", returnValue);
	      delete currentThread->space;
	      if(AddrSpace::GetNbAddrSpaces() == 0) {
		interrupt->Halt();
	      } else {
		currentThread->Finish();
	      }
	      break;
	    }
	  case SC_PutChar:
	    {
	      DEBUG ('s', "PutChar\n");
	      int c = machine->ReadRegister(4);
	      synchConsole->SynchPutChar(c);
	      break;
	    }
	  case SC_PutString:
	    {
	      DEBUG ('s', "PutString\n");
	      int from = machine->ReadRegister(4);
	      char stringBuffer[MAX_STRING_SIZE+1];
	      int nbChar;
	      do{
		nbChar = copyStringFromMachine(from, stringBuffer, MAX_STRING_SIZE);
		synchConsole->SynchPutString(stringBuffer);
		from+=nbChar;
	      }while(nbChar != 0);
	      break;
	    }
          case SC_GetChar:
            {
              DEBUG('s', "GetChar\n");
              int character = synchConsole->SynchGetChar();
              machine->WriteRegister(2, character);
              break;
            }
	  case SC_GetString:
	    {
	      DEBUG('s', "GetString\n");
	      int to = machine->ReadRegister(4);
	      int n = machine->ReadRegister(5) - 1;
	      char* stringBuffer = new char[MAX_STRING_SIZE+1];
	      int size;
	      do{
		size = synchConsole->SynchGetString(stringBuffer, std::min(MAX_STRING_SIZE, n));
		n-=size;
		copyStringToMachine(to, stringBuffer, size);
		to+=size;
	      }while(size != 0 && stringBuffer[size-1] != '\n');
	      delete stringBuffer;
	      break;
	    }
	  case SC_PutInt:
	    {
	      DEBUG('s', "PutInt\n");
	      int toPut = machine->ReadRegister(4);
	      char stringBuffer[12];
	      snprintf(stringBuffer, 12, "%d", toPut);
	      synchConsole->SynchPutString(stringBuffer);
	      break;
	    }
	   case SC_GetInt:
	    {
	      DEBUG('s', "GetInt\n");
	      int addrInt = machine->ReadRegister(4);
	      char stringBuffer[13];
	      int buffTmp;
	      synchConsole->SynchGetString(stringBuffer, 12);
	      sscanf(stringBuffer, "%d", &buffTmp);
	      copyIntToMachine(buffTmp, addrInt);
	      break;
	    }
	   case SC_ThreadCreate:
	    {
	      DEBUG('s', "ThreadCreate\n");
	      int f = machine->ReadRegister(4);
	      int arg = machine->ReadRegister(5);
	      int exitAddress = machine->ReadRegister(6);
	      int ret = do_createThread(f, arg, exitAddress);
	      machine->WriteRegister(2, ret);
	      break;
	    }
	   case SC_ThreadExit:
	    {
	      DEBUG('s', "ThreadExit\n");
	      do_ThreadExit();
	      break;
	    }
	  case SC_ForkExec:
	    {
	      DEBUG('s', "ForkExec\n");
	      int from = machine->ReadRegister(4);
	      char stringBuffer[256];
	      copyStringFromMachine(from, stringBuffer, 256);
	      int ret = do_ForkExec(stringBuffer);
	      machine->WriteRegister(2, ret);
	      break;
	    }
#endif //CHANGED
	  default:
	    {
	      printf("Unimplemented system call %d\n", type);
	      ASSERT(FALSE);
	    }
	  }

	// Do not forget to increment the pc before returning!
	UpdatePC ();
	break;
      }

    case PageFaultException:
      if (!type) {
	printf("NULL dereference at PC %x!\n", machine->registers[PCReg]);
	ASSERT (FALSE);
      } else {
	printf ("Page Fault at address %x at PC %x\n", type, machine->registers[PCReg]);
	ASSERT (FALSE);	// For now
      }

    default:
      printf ("Unexpected user mode exception %d %d at PC %x\n", which, type, machine->registers[PCReg]);
      ASSERT (FALSE);
    }
}
