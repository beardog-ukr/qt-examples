#ifndef __LambdasWithObjects__
#define __LambdasWithObjects__

#include <vector>

class SimpleArr {
  public:
    SimpleArr() ;
    // returns the number of ints greater than criterion
    int getCountOverInternalLimit();
  protected:
    std::vector<int> arr;
    int limit;
};

void lambdasWithObjectsMain();

#endif
