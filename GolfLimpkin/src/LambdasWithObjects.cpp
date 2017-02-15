#include <QDebug>

#include <math.h>
#include <algorithm>
#include <functional>
#include <vector>

#include "LambdasWithObjects.h"

using namespace std;

// ============================================================================

SimpleArr::SimpleArr() {
  arr = {3,4,5,6,12,34,5};
  limit = 10;
}

// ============================================================================

int SimpleArr::getCountOverInternalLimit() {
  int result = 0;
  for_each(arr.begin(), arr.end(), [this, &result](int elem) {
    if (elem>limit) {
      result++;
    }
  });

  return result;
}

// ============================================================================

void lambdasWithObjectsMain() {
  qDebug() << "Lambdas with objects:";

  SimpleArr sarr;
  qDebug() << "Over limit " << sarr.getCountOverInternalLimit() << " elements" ;

  qDebug() << "";
}

// ============================================================================
// ============================================================================
