#include "syscall.h"
void print(char c, int n){
  int i;

  for (i = 0; i < n; i++) {
    PutChar(c + i);
  }
  PutChar('\n');

}
int main(){
  PutString("1234567\n");
  PutString("1aazer\n"); 
  PutString("1wxcvb\n");
  return 0;
}
