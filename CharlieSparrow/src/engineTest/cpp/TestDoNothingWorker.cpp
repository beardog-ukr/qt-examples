#include "TestEngine.h"
#include "DoNothingWorker.h"

// ============================================================================
// ============================================================================
// ============================================================================

void TestEngine::DoNothingWorker_processSomeData_BasicA() {
  QByteArray barr;
  readFile(":/DoNothingWorker/Basic.txt", barr);

  QString data = QString::fromUtf8(barr);

  DoNothingWorker dnw;
  bool tmpb =  dnw.processSomeData(data);
  QString tmps = "";
  QCOMPARE(dnw.getErrorMessage(), tmps);
  QCOMPARE(tmpb, true);

  QCOMPARE(dnw.getFinalValue(), 20 );
  //QCOMPARE(etl.getToken().compare("36d04feffe8093d08f9f11ca2b9fdf3057e929e5+\\"), 0 );
}
