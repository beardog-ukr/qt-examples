#include "DoNothingAction.h"
#include "DoNothingWorker.h"

#include <QCommandLineParser>

#include <QDebug>

// === =======================================================================
// === =======================================================================

DoNothingAction::DoNothingAction(QObject *parent)
                :ActionBasic(parent){
  worker = 0;
}

// === =======================================================================

DoNothingAction::~DoNothingAction() {
  delete worker;
}

// === =======================================================================

QList<QPair<QString, QString> > DoNothingAction::commandLineOptions() {
  QList<QPair<QString, QString> > result ;

  QPair<QString, QString> p;
  p.first= "opt";
  p.second= "SOme example option" ;
  result.append(p);

  return result;
}

// === =======================================================================

bool DoNothingAction::loadCommandLineOptions(const QList<QPair<QString, QString> > options) {
  QString tmps;

  QList<QPair<QString, QString> >::const_iterator oi = options.constBegin();
  for(; oi!=options.constEnd(); oi++) {
    if (oi->first == "opt") {
      qDebug() << "Got option: " << oi->second ;
    }
  }

  // check if loaded everything needed


  //finally
  qDebug() << "Loaded command line" ;
  return true;
}

// === =======================================================================

bool DoNothingAction::startAction() {  
  worker = new DoNothingWorker(this);
  // pageReader->setSomething(something);
  connect(worker, SIGNAL(finished()), this, SLOT(processResult()) ) ;
  //
  bool started = worker->start();
  if (!started) {
    errorMessage = worker->getErrorMessage();
    delete worker;
    worker = 0;
  }

  qDebug() << "Started action" << started;
  return started;
}

// === =======================================================================

void DoNothingAction::processResult() {
  const QString em = worker->getErrorMessage();
  if (!em.isEmpty()) {
    errorMessage = em;
    emit actionFailure();
    return;
  }

  int fv = worker->getFinalValue();
  qDebug() << "Got value " << fv ;

  delete worker;
  worker = 0;

  emit actionDone();
}

// === =======================================================================
// === =======================================================================
