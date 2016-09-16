#include "TestFileProcessor.h"

int main(int , char **)
{
  QStringList testCmd;
  TestFileProcessor testFileProcessor;
  QTest::qExec(&testFileProcessor,testCmd);

  return 0;
}
