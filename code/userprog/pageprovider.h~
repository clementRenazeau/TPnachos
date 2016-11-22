#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H

#include "bitmap.h"

class PageProvider{
 public:
  PageProvider(int nbPages);
  ~PageProvider();
  int GetEmptyPage();
  void ReleasePage(int pageNum);
  int NumAvailPage();
  
 private:
  BitMap *pages;
};

#endif //PAGEPROVIDER_H
