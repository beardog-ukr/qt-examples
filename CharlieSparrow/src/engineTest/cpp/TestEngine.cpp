#include "TestEngine.h"

#include <QFile>
#include <QTextStream>

// ============================================================================
// ============================================================================
// ============================================================================

void TestEngine::readFile(const QString fileName, QByteArray& ba) {
  QFile data(fileName);
  if ( !data.open(QFile::ReadOnly)) {
    QFAIL( "Problem opening file ()" );
  }

  ba.clear();
  ba.append(data.readAll());

  data.close();
}

// ============================================================================
