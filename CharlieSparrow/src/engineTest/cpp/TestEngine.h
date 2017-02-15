#ifndef __TestEngine__
#define __TestEngine__

#include <QtTest/QtTest>

#include <QString>
#include <QByteArray>

class TestEngine: public QObject
{
  Q_OBJECT
private slots:
  void DoNothingWorker_processSomeData_BasicA();

private:
  void readFile(const QString fileName, QByteArray& data) ;
};

#endif
