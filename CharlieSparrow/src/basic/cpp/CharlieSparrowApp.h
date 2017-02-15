#ifndef __CharlieSparrowApp__
#define __CharlieSparrowApp__

#include <QObject>
#include <string>

class ActionBasic;
class QTimer;

#include <QStringList>

class CharlieSparrowApp : public QObject
{
  Q_OBJECT
//  friend class TestCharlieSparrowApp;
public:
  CharlieSparrowApp(QObject *parent = 0);
  virtual ~CharlieSparrowApp();

  bool prepareToStart();
  bool processCommandLine();

  int getAppExitCode() const;

public slots:
  void startEveryting();
  void processActionResult();
  void processActionFailure();

protected:
  ActionBasic* actionPerformer;
  QTimer* startupTimer;
  int appExitCode ;
};

#endif
