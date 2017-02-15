#include <QDebug>

#include <math.h>
#include <functional>

#include "BasicLambdas.h"

// ============================================================================

int calclulate(int a, int b, std::function<int(int,int)> calcFunc) {
  int result = calcFunc(a,b);
  return result;
}

// ============================================================================

int calclulateUsual(int a, int b, int (*calcFunc)(int, int)) {
  int result = calcFunc(a,b);
  return result;
}

// ============================================================================

template <typename CalcFunction>
int calclulateTemplated(int a, int b, CalcFunction && calcFunc) {
  int result = calcFunc(a,b);
  return result;
}

// ============================================================================

void basicLambdasMain() {
  qDebug() << "Basic Lambdas:";

  int firstNumber = 10;
  int secondNumber = 20;

  int sum = calclulate(firstNumber, secondNumber, [](int a, int b) {
    return (a+b);
  });
  qDebug() << "Added "<< firstNumber << " and " << secondNumber
           << " received " << sum;

  int sumX = calclulate(firstNumber, secondNumber, [](int a, int b)->int {
    int sum = a+b;
    return std::lround(sum*1.2);
  } );
  qDebug() << "Added "<< firstNumber << " and " << secondNumber
           << " received " << sumX << " (bonus 20%)";

  int sumU = calclulateUsual(firstNumber, secondNumber, [](int a, int b) {
    return (a+b);
  });
  qDebug() << "Added "<< firstNumber << " and " << secondNumber
                    << " received " << sumU << "(used old form)";

  int sumT = calclulateTemplated(firstNumber, secondNumber, [](int a, int b) {
    return (a+b);
  });
  qDebug() << "Added "<< firstNumber << " and " << secondNumber
           << " received " << sumT << "(used template)";


  std::function<int (int)> factorial = [&] (int i) { 
    return (i == 1) ? 1 : i * factorial(i - 1); 
  };

  qDebug() << "5! ==" << factorial(5);
		   
  qDebug() << "";
}


// ============================================================================
// ============================================================================
