#include <QtTest/QtTest>
#include <QStringList>

#include <QStringList>

class TestFileProcessor: public QObject
{
    Q_OBJECT
private slots:
  void processData_BasicA();
  void processData_BasicB();
  void processData_Equal();

protected:
  QStringList data_BasicA;
  QStringList data_BasicB;
  QStringList data_Equal;

  QStringList readFile(const QString fileName) ;
};
