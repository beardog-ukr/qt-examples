#ifndef __DoNothingAction__
#define __DoNothingAction__

#include "ActionBasic.h"
class DoNothingWorker ;

#include <QList>
#include <QPair>
#include <QString>

// === =======================================================================

// This is action template;

class DoNothingAction : public ActionBasic {
  Q_OBJECT
  friend class TestBasic;
public:
  DoNothingAction(QObject *parent = 0);
  virtual ~DoNothingAction();

  static QList<QPair<QString, QString> > commandLineOptions();
  virtual bool loadCommandLineOptions(const QList<QPair<QString, QString> > options);

  virtual bool startAction();

protected slots:
  void processResult();

protected:
  DoNothingWorker* worker ;
};

#endif
