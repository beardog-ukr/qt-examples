#include <QDebug>

#include <math.h>
#include <algorithm>
#include <functional>
#include <vector>

#include "ScopeLambdas.h"

using namespace std;
// ============================================================================
//
// int calclulate(int a, int b, std::function<int(int,int)> calcFunc) {
//   int result = calcFunc(a,b);
//   return result;
// }

// ============================================================================

void scopeLambdasMain() {
  qDebug() << "Scope Lambdas:";

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  qDebug() << "Two functions:";
  int tfValue = 42;
  auto f1 = [tfValue]() {
    qDebug() << "F1 prints " << tfValue;
    //side note, following line causes compiler error
    //tfValue = 44; // errror, assigning value to passed by value
  };

  tfValue = 314;
  auto f2 = [tfValue]() {
    qDebug() << "F2 prints " << tfValue;
  };

  f1();
  f2();

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  qDebug() << "Two functions (by ref): ";
  int tfrValue = 42;
  auto fr1 = [&tfrValue]() {
    qDebug() << "F1 prints " << tfrValue << "(passed by ref)";
  };

  fr1(); // call before value was changed

  tfrValue = 314;
  auto fr2 = [&tfrValue]() {
    qDebug() << "F2 prints " << tfrValue << "(passed by ref)";
  };

  fr1(); // now we call this function after value was changed
  fr2();


  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  qDebug() << "Vector pretty print";

  vector<int> v = {10, 15, 20, 25};
  for_each(v.begin(), v.end(), [](int elem) {
    qDebug() << "-=< " << elem << " >=-";
  });

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  qDebug() << "Sum array elements (with bonus):";

  vector<int> v2 = {1, 15, 20, 5};
  int sum=0;
  int bonusThreshold = 8;
  for_each(v2.begin(), v2.end(), [&sum, bonusThreshold](int elem) {
    sum += elem ;
    if (elem>=bonusThreshold) {
      sum += 1;
    }
  });

  qDebug() << "Sum is " << sum << "(like 1+(15+1)+(20+1)+5)";

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  qDebug() << "Mutable functions: :";
  int mfValue = 42;
  auto mf1 = [mfValue](QString message) mutable {
    qDebug() << message << ": " << mfValue;
    mfValue = mfValue +5; // no compile error
  };

  mf1("mf1 first call");
  auto mf2 = mf1;

  mf1("mf1 second call");
  mf1("mf1 third call");
  mf2("mf2 first call");
  

  //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  qDebug() << "";
}


// ============================================================================
// ============================================================================
