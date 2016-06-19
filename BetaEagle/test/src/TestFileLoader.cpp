#include "TestFileLoader.h"

#include "FileLoader.h"

void TestFileLoader::getErrorMessage_A()
{
  FileLoader fileLoader;

  QString em = fileLoader.getErrorMessage();

  QCOMPARE(em, QString("") );
}

// ============================================================================

void TestFileLoader::loadFile_ErrA()
{
  FileLoader fileLoader;

  bool loaded = fileLoader.loadFile("foo/bar");

  QString em = fileLoader.getErrorMessage();
  QCOMPARE(em.isEmpty(), false);

  QCOMPARE(loaded, false);
}
