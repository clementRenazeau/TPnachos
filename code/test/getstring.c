#include "syscall.h"
void print(char c, int n){
  int i;

  for (i = 0; i < n; i++) {
    PutChar(c + i);
  }
  PutChar('\n');

}
int main(){
  char tab[6];
  GetString(tab, 6);
  PutString(tab);
  GetString(tab, 6);
  PutString(tab);
  return 0;
}
