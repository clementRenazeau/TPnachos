#include "syscall.h"
int main() {
	int c = GetChar();
	PutChar(c);
	return 1;
}
