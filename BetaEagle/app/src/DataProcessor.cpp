#include <QDebug>

#include <QFile>

#include "DataProcessor.h"

// ============================================================================

DataProcessor::DataProcessor() {
  resultValue = 0; // default value
  errorMessage = "";
}

// ============================================================================

DataProcessor::~DataProcessor() {
  // nothing to do here
}

// ============================================================================

QString DataProcessor::getErrorMessage() const {
  return errorMessage;
}

// ============================================================================

bool DataProcessor::process(const QStringList& strValues) {
  bool result = true;

  QStringList::const_iterator svi;
  for (svi = strValues.constBegin(); svi != strValues.constEnd(); ++svi)
  {
    //qDebug() << "got line: " << line;
    const QString line = (*svi);
    bool convOk = true;
    int ti = line.toInt(&convOk, 10);
    if (!convOk) {
      errorMessage = "Failed to convert some line (" + line.left(9) + ")";
      result = false;
      break;
    }
    else {
      if (ti>resultValue) {
        resultValue = ti;
      }
    }
  }

  return result;
}

// ============================================================================

int DataProcessor::getResult() const {
  return resultValue;
}

// ============================================================================
