#include <QtCore/QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>

#include "FileProcessor.h"

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  //qDebug() << "Started";

  QCommandLineParser parser;
  parser.setApplicationDescription("The \"BetaFalcon\" app reads integers from a file and prints max value");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("source", QCoreApplication::translate("main", "Source file to process. Should contain integer numbers, one per line"));

  parser.process(app);

  const QString sourceFileName = parser.positionalArguments().at(0);

  FileProcessor fileProcessor;

  if (!fileProcessor.loadFile(sourceFileName)) {
    qDebug() << "Error: " << fileProcessor.getErrorMessage();
    return 1;
  }
//else

  qDebug() << "Max value is " << fileProcessor.getResult();

  return 0;//app.exec();
}
