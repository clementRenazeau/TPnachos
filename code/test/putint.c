#include "syscall.h"

int main(){
  int v = 1;
  PutInt(v);
  //v = –2147483648;
  v = -1;
  PutInt(v);
  return 0;
}
