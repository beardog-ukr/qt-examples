#include <QDebug>

#include <QFile>
#include <QTextStream>

#include "FileProcessor.h"

// ============================================================================

FileProcessor::FileProcessor() {
  errorMessage = "";
  resultValue = -1;
}

// ============================================================================

FileProcessor::~FileProcessor() {
  // nothing to do here
}

// ============================================================================

QString FileProcessor::getErrorMessage() const {
  return errorMessage;
}

// ============================================================================

bool FileProcessor::loadFile(const QString fileName) {
  bool result = true;

  QFile data(fileName);
  if ( !data.open(QFile::ReadOnly)) {
    errorMessage = "Problem opening file (" + QString::number(data.error()) + ")";
    return false;
  }

  QTextStream ts(&data);
  QString line;
  QStringList rawLines;
  while (ts.readLineInto(&line)) {
    //qDebug() << "got line: " << line;
    rawLines.append(line);
  }

  data.close();

  // now main action
  result = processData(rawLines);
  return result;
}

// ============================================================================

int FileProcessor::getResult() const {
  return resultValue;
}

// ============================================================================


bool FileProcessor::processData(const QStringList& rawData){
  if (rawData.size()==0) {
    errorMessage = "Loaded list is empty";
    return false;
  }

  errorMessage = "";
  resultValue = -1;

  QStringList::const_iterator svi;
  for (svi = rawData.constBegin(); svi != rawData.constEnd(); ++svi)  {
    //qDebug() << "got line: " << line;
    const QString line = (*svi);
    bool convOk = true;
    int ti = line.toInt(&convOk, 10);
    if (!convOk) {
      errorMessage = "Failed to convert some line (" + line.left(9) + ")";
      return false;
    }
    else {
      if (ti<0) {
        errorMessage = "One of values is negative (" + QString::number(ti) + ")";
        return false;
      }
      if (ti>resultValue) {
        resultValue = ti;
      }
    }
  }

  return errorMessage.isEmpty() ;
};
