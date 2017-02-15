#include "DoNothingWorker.h"

#include <QStringList>
#include <QTimer>
#include <QDebug>
// === =======================================================================
// === =======================================================================

DoNothingWorker::DoNothingWorker(QObject* parent)
                :QObject(parent) {
  errorMessage = "";
  finalValue = -1;
  taskTimer = 0;
}

// === =======================================================================

DoNothingWorker::~DoNothingWorker() {
  delete taskTimer ;
}

// === =======================================================================

QString DoNothingWorker::getErrorMessage() const {
  return errorMessage;
}

// === =======================================================================

int DoNothingWorker::getFinalValue() const {
  return finalValue;
}

// === =======================================================================

bool DoNothingWorker::start() {
  bool result = true;

  taskTimer = new QTimer(this) ;
  taskTimer->setSingleShot(true);
  connect(taskTimer, SIGNAL(timeout()),this, SLOT(processSomething()) );
  taskTimer->start(5000);

  qDebug() << "Worker started" ;
  return result;
}

// === =======================================================================

void DoNothingWorker::processSomething() {
  qDebug() << "Worker done" ;

  processSomeData("44;55;22");

  emit finished();
}

// === =======================================================================

bool DoNothingWorker::hasError() const {
  return !errorMessage.isEmpty();
}

// === =======================================================================

bool DoNothingWorker::processSomeData(const QString& data) {

  QStringList sl = data.split(";") ;
  if (sl.count()==0) {
    errorMessage = "Empty list";
    return false;
  }

  bool  tmpb = true;
  finalValue = sl.at(0).toInt(&tmpb);
  if (!tmpb) {
    errorMessage = "Failed to convert (" + sl.at(0) + ")";
    return false;
  }

  return true;
}

// === =======================================================================
