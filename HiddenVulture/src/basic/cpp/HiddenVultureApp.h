#ifndef __HiddenVultureApp__
#define __HiddenVultureApp__

#include <QObject>
#include <QString>

class FiveCatsLogger;
class QTimer;
class MainForm;
class VideoReader;
#include "PlayingOptions.h"

#include <QStringList>

class HiddenVultureApp : public QObject
{
  Q_OBJECT
//  friend class TestHiddenVultureApp;
public:
  HiddenVultureApp(QObject *parent = 0);
  virtual ~HiddenVultureApp();

  bool prepareToStart();
  bool processCommandLine();

  int getAppExitCode() const;

protected slots:
  void videoReaderReady(int delay) ;

protected:
  MainForm* mainForm;
  VideoReader* videoReader;
  QString vfn;

  PlayingOptions playingOptions;
  bool prepareVideoReaderThread();

  QTimer* controlTimer;

  int appExitCode ;
  FiveCatsLogger* c5;
};

#endif
