#ifdef USER_PROGRAM
#include "sysutils.h"
#include "system.h"

int copyStringFromMachine(int from, char *to, unsigned int size) {
    unsigned int pos = 0;
    int buf = 0;
    machine->ReadMem(from+pos, 1, &buf);
    while((buf != 0) && (pos < size)) {
        to[pos++] = buf;
        machine->ReadMem(from+pos, 1, &buf);
    }
    to[pos] = 0;
    return pos;
}
void copyStringToMachine(int to, char* from, unsigned int size){
  unsigned int pos = 0;
  for(; from[pos] != 0 && (pos < size) ; ++pos) {
    machine->WriteMem(to+pos, 1, from[pos]);
  }
  machine->WriteMem(to+pos, 1, 0);
}
void copyIntToMachine(int valeur, int to){
  machine->WriteMem(to, 4, valeur);
}
#endif
