#include "syscall.h"

#define THIS "aaa"
#define THAT "bbb"
const int N = 10; // Choose it large enough!
void puts(const char *s) {
  const char *p;
  for (p = s; *p != '\0'; p++)
    PutChar(*p);
}
void f(void *arg) {
  const char *s = arg;
  int i;
  for (i = 0; i < N; i++)
    puts(s);
  PutChar('\n');
}
int main() {
  int i;
  for(i=0; i<12; ++i) {
    ThreadCreate(f, THIS);
  }
  f(THAT);
  return 0;
}
