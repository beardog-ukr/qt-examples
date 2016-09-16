#include "TestFileProcessor.h"

#include "FileProcessor.h"

// ============================================================================

QStringList TestFileProcessor::readFile(const QString fileName) {
  QStringList result;
  QFile data(fileName);
  if ( !data.open(QFile::ReadOnly)) {
//    QFAIL( "Problem opening file (" + QString::number(data.error()) + ")" );
    return result;
  }

  QTextStream ts(&data);
  result = ts.readAll().split("\n");
  data.close();

  return result;
}

// ============================================================================

void TestFileProcessor::processData_BasicA()
{
  QStringList sl = readFile(":/TestFileProcessor_BasicA.txt");
  FileProcessor fileProcessor;
  bool processingResult = fileProcessor.processData(sl);
  int resultValue = fileProcessor.getResult();
  QCOMPARE(processingResult, true);
  QCOMPARE(resultValue, 111);
}

// ============================================================================

// Here max value comes last
void TestFileProcessor::processData_BasicB()
{
  QStringList sl = readFile(":/TestFileProcessor_BasicB.txt");
  FileProcessor fileProcessor;
  bool processingResult = fileProcessor.processData(sl);
  int resultValue = fileProcessor.getResult();
  QCOMPARE(processingResult, true);
  QCOMPARE(resultValue, 983);
}

// ============================================================================

void TestFileProcessor::processData_Equal()
{
  QStringList sl = readFile(":/TestFileProcessor_Equal.txt");
  FileProcessor fileProcessor;
  bool processingResult = fileProcessor.processData(sl);
  int resultValue = fileProcessor.getResult();
  QCOMPARE(processingResult, true);
  QCOMPARE(resultValue, 11);
}

// ============================================================================
