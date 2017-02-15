#include <QDebug>

#include <math.h>
#include <functional>

#include "LambdaGenerator.h"

// ============================================================================

std::function<int(int,int)> //this is the type of return value
generator(int processingId) {
  if (processingId==1) {
    return [](int a, int b) ->int {
      return (a+b);
    };
  }

  int bonus = 20;
  if (processingId == 2) {
    return [&bonus](int a, int b) ->int {
      bonus++;
      return (a+b+bonus);
    };
  }

  return [bonus](int a, int b) ->int {
    return (a+b+bonus);
  };
}

// ============================================================================

void lambdaGeneratorMain() {
  qDebug() << "Lambda Generator:";

  auto f1 = generator(1); // simple adding without bonus
  int s1 = f1(1,2);
  qDebug() << "Added 1+2, got "<< s1 ;

  auto f0 = generator(0); // adding with bonus
  qDebug() << "Added 1+2, got "<< f0(1,2) << "(with bonus)" ;
  qDebug() << "Added 6+2, got "<< f0(6,2) << "(with bonus)" ;
  qDebug() << "Added 8+2, got "<< f0(8,2) << "(with bonus)" ;

  auto f2 = generator(2); // this causes segfault
  qDebug() << "Added 1+2, got "<< f2(1,2) ;
  qDebug() << "Added 6+2, got "<< f2(6,2) ;
  qDebug() << "Added 8+2, got "<< f2(8,2) ;

  qDebug() << "";
}


// ============================================================================
// ============================================================================
