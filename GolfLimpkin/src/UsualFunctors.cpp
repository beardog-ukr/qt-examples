#include <QDebug>

#include <vector>
#include <algorithm>

#include "UsualFunctors.h"

// ============================================================================

using namespace std;

// ============================================================================

struct NicePrinter {
  void operator()(int n) const {
    // adds nice brackets to printed value
    qDebug() << "-=<( " << n << " )>=-";
  }
};

// ============================================================================

void usualFunctorsMain() {
  qDebug() << "Usual Functors:";

  vector<int> v;
  v.push_back(10);
  v.push_back(15);
  v.push_back(20);

  for_each(v.begin(), v.end(), NicePrinter());

  qDebug() << "";
}


// ============================================================================
// ============================================================================
