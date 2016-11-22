#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H

#include "bitmap.h"
#include "synch.h"
class PageProvider{
 public:
  PageProvider(int nbPages);
  ~PageProvider();
  int GetEmptyPage();
  void ReleasePage(int pageNum);
  int NumAvailPage();
  
 private:
  BitMap *pages;
  Semaphore *s;
};

#endif //PAGEPROVIDER_H
