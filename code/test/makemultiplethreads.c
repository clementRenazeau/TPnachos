#include "syscall.h"

void f(int n){
  volatile int i = 0;
  for(i = 0 ; i < n ; ++i){
  }
  PutInt(i);
  PutChar('\n');
  //ThreadExit();
}

int main(){
  ThreadCreate(f, 10000);
  ThreadCreate(f, 10000);
  ThreadCreate(f, 10000);
  return 0;
}
