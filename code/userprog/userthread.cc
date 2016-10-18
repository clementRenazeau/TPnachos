#include "thread.h"
#include "machine.h"
#include "system.h"

#ifdef USER_PROGRAM
static void StartUserThread(void *schmurtz);
struct ThreadParameters {
    int function;
    int argument;
};

int do_createThread(int f, int arg) {
    Thread *newThread = new Thread("userThread");
    ThreadParameters *p = new ThreadParameters {f, arg};
    newThread->Start(StartUserThread, p);
    return 0;
}

void StartUserThread(void *schmurtz) {
    ThreadParameters *p = static_cast<ThreadParameters*>(schmurtz);

    for (int i = 0; i < NumTotalRegs; i++) {
        machine->WriteRegister (i, 0);
    }

    machine->WriteRegister (PCReg, p->function);

    machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);

    machine->WriteRegister (StackReg, currentThread->space->getStackSize() - 16 - 256);
    DEBUG ('a', "Initializing stack register to 0x%x\n",
            currentThread->space->getStackSize() - 16 - 256);
}
int AllocateUserStack() {

}
#endif
