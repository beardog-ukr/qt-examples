#include <QtTest/QtTest>
//#include <QStringList>

class TestFileLoader: public QObject
{
    Q_OBJECT
private slots:
    void getErrorMessage_A();
    void loadFile_ErrA();
};
