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
  return 0;
}
