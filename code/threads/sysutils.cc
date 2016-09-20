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
