#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"
static Semaphore *readAvail;
static Semaphore *writeDone;
static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }
SynchConsole::SynchConsole(const char *in, const char *out){
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    console = new Console (in, out, ReadAvailHandler, WriteDoneHandler, 0);
}
SynchConsole::~SynchConsole(){
    delete console;
    delete writeDone;
    delete readAvail;
}
void SynchConsole::SynchPutChar(int ch){
    console->PutChar (ch);
    writeDone->P ();

}
int SynchConsole::SynchGetChar(){
    readAvail->P ();
    return console->GetChar ();
}
void SynchConsole::SynchPutString(const char s[]){
    for(int i=0; s[i] != 0; ++i){
        this->SynchPutChar(s[i]);
    }
}
void SynchConsole::SynchGetString(char *string, int size){
    int currentChar;
    int pos = 0;
    while(pos < size && (currentChar = this->SynchGetChar()) != EOF && currentChar != '\n') {
        string[pos] = currentChar;
        pos++;
    }
    string[pos] = 0;
    return pos;
}
#endif // CHANGED
