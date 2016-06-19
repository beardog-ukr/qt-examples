#include <QtCore/QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>

#include "DataProcessor.h"
#include "FileLoader.h"

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  //qDebug() << "Started";

  QCommandLineParser parser;
  parser.setApplicationDescription("The \"BetaEagle\" app reads integers from a file and prints max value");
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("source", QCoreApplication::translate("main", "Source file to process. Should contain integer numbers, one per line"));

  parser.process(app);

  const QString sourceFileName = parser.positionalArguments().at(0);

  FileLoader fileLoader;

  if (!fileLoader.loadFile(sourceFileName)) {
    qDebug() << "Error: " << fileLoader.getErrorMessage();
    return 1;
  }
//else

  DataProcessor dataProcessor;
  if (!dataProcessor.process(fileLoader.getResult())) {
    qDebug() << "Error: " << dataProcessor.getErrorMessage();
    return 1;
  }

  qDebug() << "Max value is " << dataProcessor.getResult();

  return 0;//app.exec();
}
