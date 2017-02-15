#ifndef __ActionBasic__
#define __ActionBasic__

#include <QList>
#include <QObject>
#include <QPair>
#include <QString>

class ActionBasic: public QObject
{
  Q_OBJECT
  friend class TestBasic;
public:
  ActionBasic(QObject *parent = 0);
  virtual ~ActionBasic();

  virtual bool startAction() =0;

  virtual bool loadCommandLineOptions(const QList<QPair<QString, QString> > options)=0 ;

  QString getErrorMessage() const;

signals:
  void actionDone();
  void actionFailure();

protected:
  QString errorMessage;
};

#endif
