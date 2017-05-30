#include <QApplication>

#include <QDebug>

#include "HiddenVultureApp.h"

//=============================================================================
//=============================================================================
//=============================================================================

int main(int argc, char* argv[])
{
  QApplication app(argc,argv);
  HiddenVultureApp hiddenVultureApp;

  if (!hiddenVultureApp.processCommandLine()) {
    return hiddenVultureApp.getAppExitCode();
  }

  if (!hiddenVultureApp.prepareToStart()) {
    return hiddenVultureApp.getAppExitCode();
  }

  const int aer =  app.exec();

  return aer;
}
