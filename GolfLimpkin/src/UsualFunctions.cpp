#include <QDebug>

#include <math.h>

#include "UsualFunctions.h"

// ============================================================================

int addNumbers(int a, int b) {
  return (a+b);
}

// ============================================================================

int addNumbersExtra20(int a, int b) {
  int sum = a+b;
  return std::lround(sum*1.2);
}

// ============================================================================

int calclulate(int a, int b, int (*calcFunc)(int, int)) {
  int result = calcFunc(a,b);
  return result;
}

// ============================================================================

void usualFunctionsMain() {
  qDebug() << "Usual Functions:";

  int firstNumber = 10;
  int secondNumber = 20;

  int sum = calclulate(firstNumber, secondNumber, &addNumbers);
  qDebug() << "Added "<< firstNumber << " and " << secondNumber
           << " received " << sum;

  int sumX = calclulate(firstNumber, secondNumber, &addNumbersExtra20);
  qDebug() << "Added "<< firstNumber << " and " << secondNumber
           << " received " << sumX << " (bonus 20%)";

  qDebug() << "";
}


// ============================================================================
// ============================================================================
