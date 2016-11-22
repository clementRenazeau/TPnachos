#include "pageprovider.h"
#include "system.h"

PageProvider::PageProvider(int nbPages){
  s = new Semaphore("mutex",1);
  pages = new BitMap(nbPages);
}

PageProvider::~PageProvider(){
  delete pages;
  delete s;
}

int PageProvider::GetEmptyPage(){
  s->P();
  int page = pages->Find();
  s->V();
  if(page != -1){
    char* addr = & machine->mainMemory[page*PageSize];
    memset(addr, 0, PageSize);
  }
  return page;
}

void PageProvider::ReleasePage(int pageNum){
  s->P();
  pages->Clear(pageNum);
  s->V();
}

int PageProvider::NumAvailPage(){
  s->P();
  int tmp = pages->NumClear();
  s->V();
  return tmp;
}
