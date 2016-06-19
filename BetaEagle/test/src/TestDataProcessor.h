#include <QtTest/QtTest>
#include <QStringList>


class TestDataProcessor: public QObject
{
    Q_OBJECT
private slots:
    void process_BasicA();
    void process_Equal();
    void process_BasicB();
};
