#include <QtCore/QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>

#include "BasicLambdas.h"
#include "LambdaGenerator.h"
#include "LambdasWithObjects.h"
#include "ScopeLambdas.h"
#include "UsualFunctions.h"
#include "UsualFunctors.h"

// ============================================================================

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  //qDebug() << "Started";

  QCommandLineParser parser;
  parser.setApplicationDescription("The \"GolfLimpkin\" app shows some examples of lambda functions in C++");
  parser.addHelpOption();
  parser.addVersionOption();
//  parser.addPositionalArgument("source", QCoreApplication::translate("main", "Source file to process. Should contain integer numbers, one per line"));

  parser.process(app);

//  const QString sourceFileName = parser.positionalArguments().at(0);

  usualFunctionsMain();
  basicLambdasMain();

  usualFunctorsMain();
  scopeLambdasMain();

  lambdasWithObjectsMain();

  lambdaGeneratorMain();

  return 0;//app.exec();
}
