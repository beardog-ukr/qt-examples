#include <QCoreApplication>

#include <QDebug>

#include "CharlieSparrowApp.h"

//=============================================================================
//=============================================================================
//=============================================================================

int main(int argc, char* argv[])
{
  QCoreApplication app(argc,argv);
  CharlieSparrowApp charlieSparrowApp;

  if (!charlieSparrowApp.processCommandLine()) {
    return charlieSparrowApp.getAppExitCode();
  }

  if (!charlieSparrowApp.prepareToStart()) {
    return charlieSparrowApp.getAppExitCode();
  }

  return app.exec();
}
