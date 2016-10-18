#include "syscall.h"

void f(int n){
  int i = 0;
  for(i = 0 ; i < n ; ++i){
    PutChar('a' + i);
  }
  ThreadExit();
}

int main(){
  ThreadCreate(f, 3);
  PutChar('z');
  while(1);
  return 0;
}
