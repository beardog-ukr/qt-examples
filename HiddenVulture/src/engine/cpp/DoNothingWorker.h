#ifndef __DoNothingWorker__
#define __DoNothingWorker__

#include <QObject>
#include <QString>
class QTimer;

class DoNothingWorker : public QObject
{
  Q_OBJECT
  friend class TestEngine;
public:
  DoNothingWorker(QObject* parent =0);
  virtual ~DoNothingWorker();

  bool hasError() const;
  QString getErrorMessage() const;

  int getFinalValue() const;

  virtual bool start();

protected slots:
  virtual void processSomething();

signals:
  void finished();

protected :
  QString errorMessage;
  int finalValue;
  QTimer* taskTimer ;

  bool processSomeData(const QString& data) ;
};

#endif
