#include "syscall.h"
int main() {
	int c;
        GetInt(&c);
	PutInt(c);
	return 1;
}
