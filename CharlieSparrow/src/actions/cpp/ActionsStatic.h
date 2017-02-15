#ifndef __ActionsStatic__
#define __ActionsStatic__

#include "ActionBasic.h"

#include <QList>
#include <QPair>
#include <QString>

class ActionsStatic {

public:
  static ActionBasic* createActionPerformer(const QString& actionCode, QObject* parent =0);
  static QString avilableActionCodes();

  static QList<QPair<QString, QString> > commandLineOptions();
};


#endif
