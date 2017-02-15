#include <QCoreApplication>
#include <QDebug>
#include "FoxtrotPenguin.h"

//=============================================================================
//=============================================================================
//=============================================================================

int main(int argc, char* argv[])
{
  QCoreApplication app(argc,argv);

  if (argc!=2) {
    qDebug() << "This applications must receive oe command line option and it should be an id of example to perform.";
    return 1;
  }

  FoxtrotPenguin fp;

  bool tmpb = fp.startAction(QString::fromUtf8(argv[1]));

  if (tmpb) {
    return app.exec();
  }
  else {
    return 1;
  }
}
