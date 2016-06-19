#include "TestDataProcessor.h"

#include "DataProcessor.h"

// ============================================================================

void TestDataProcessor::process_BasicA()
{
  QStringList sl;
  sl.append("11");
  sl.append("34");
  sl.append("6");

  DataProcessor dataProcessor;
  bool processingResult = dataProcessor.process(sl);
  int resultValue = dataProcessor.getResult();
  QCOMPARE(processingResult, true);
  QCOMPARE(resultValue, 34);
}

// ============================================================================

// Here max value comes last
void TestDataProcessor::process_BasicB()
{
  QStringList sl;
  sl.append("11");
  sl.append("34");
  sl.append("633");

  DataProcessor dataProcessor;
  bool processingResult = dataProcessor.process(sl);
  int resultValue = dataProcessor.getResult();
  QCOMPARE(processingResult, true);
  QCOMPARE(resultValue, 633);
}

// ============================================================================

void TestDataProcessor::process_Equal()
{
  QStringList sl;
  sl.append("11");
  sl.append("11");
  sl.append("11");
  sl.append("11");

  DataProcessor dataProcessor;
  bool processingResult = dataProcessor.process(sl);
  int resultValue = dataProcessor.getResult();
  QCOMPARE(processingResult, true);
  QCOMPARE(resultValue, 11);
}

// ============================================================================
