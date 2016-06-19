#include "TestDataProcessor.h"
#include "TestFileLoader.h"



int main(int , char **)
{
  QStringList testCmd;
  TestDataProcessor testDataProcessor;
  //QDir testLogDir;
  //testLogDir.mkdir("UnitTest_Results");
  //testCmd<<" "<<"-o" <<"UnitTest_Results/test_log.txt";
  QTest::qExec(&testDataProcessor,testCmd);

  TestFileLoader testFileLoader;
  QTest::qExec(&testFileLoader,testCmd);

  return 0;
}
