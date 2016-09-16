#include <QDebug>

#include <QFile>
#include <QTextStream>

#include "FileLoader.h"

// ============================================================================

FileLoader::FileLoader() {
  errorMessage = "";
}

// ============================================================================

FileLoader::~FileLoader() {
  // nothing to do here
}

// ============================================================================

QString FileLoader::getErrorMessage() const {
  return errorMessage;
}

// ============================================================================

bool FileLoader::loadFile(const QString fileName) {
  QFile data(fileName);
  if ( !data.open(QFile::ReadOnly)) {
    errorMessage = "Problem opening file (" + QString::number(data.error()) + ")";
    return false;
  }

  QTextStream ts(&data);
  QString line;
  while (ts.readLineInto(&line) ) {
    //qDebug() << "got line: " << line;
    lines.append(line);
  }

  data.close();

  return true;
}

// ============================================================================

QStringList FileLoader::getResult(const bool clear) {
  QStringList result = lines;
  if (clear) {
    lines.clear();
  }
  return result;
}

// ============================================================================
