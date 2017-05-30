#include "HiddenVultureApp.h"
#include "MainForm.h"
#include "FiveCatsLogger.h"
#include "VideoReader.h"
 
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QTimer>

#include <QThread>


// === =======================================================================
// === =======================================================================

HiddenVultureApp::HiddenVultureApp(QObject* parent) : QObject(parent){
//
  mainForm = 0;
  videoReader =0;

  c5 = new FiveCatsLogger();
  c5->setLogLevel(FiveCatsLogger::Debug);
}

// === =======================================================================

HiddenVultureApp::~HiddenVultureApp() {
//
  c5->t(__c5_MN__, "");

  delete mainForm;

  delete c5;
}

// === =======================================================================

bool HiddenVultureApp::processCommandLine() {
  bool result = true;

  QCommandLineParser parser;
  parser.setApplicationDescription("HiddenVultureApp loads a video file and performs some actions with it using opencv lib");
  parser.addHelpOption();
  QCoreApplication::setApplicationVersion("0.0.02");
  parser.addVersionOption();

  // command line options
  QCommandLineOption vfnOption("file");
  vfnOption.setDescription("Video file to load (*.mp4)");
  vfnOption.setValueName("file");
  parser.addOption(vfnOption);

  c5->initCommandLineParser(parser);

  // Process the actual command line arguments given by the user
  QCoreApplication* ca = QCoreApplication::instance();
  parser.process(*ca);

  c5->loadCommandLineParser(parser);
  vfn = parser.value(vfnOption);
  if (vfn.isEmpty()) {
    c5->c("Please specify file name to process") ;
    appExitCode = 1;
    result = false;
  }

  return result;
}

// === =======================================================================

bool HiddenVultureApp::prepareToStart() {

  mainForm = new MainForm(vfn, c5);
  const QString mfem = mainForm->getErrorMessage() ;
  if (!mfem.isEmpty()) {
    c5->c(mfem);
    appExitCode = 2;
    return false;
  }
  //else
  mainForm->show();

  return prepareVideoReaderThread();
}

// ============================================================================

bool HiddenVultureApp::prepareVideoReaderThread() {

  QThread* thread = new QThread;
  videoReader = new VideoReader(mainForm->getPlayingOptions());

  videoReader->moveToThread(thread);

  connect(thread, SIGNAL (started()), videoReader, SLOT (getReady()));

  connect(mainForm, SIGNAL(gettingClosed()), videoReader, SLOT(shutDown())) ;
  connect(videoReader, SIGNAL (error(QString)), mainForm, SLOT (videoReaderError(QString)));

  qRegisterMetaType<PlayingOptions>("PlayingOptions");
  connect(mainForm, SIGNAL(videoOptionsChanged(PlayingOptions)),
          videoReader, SLOT(processNewOptions(PlayingOptions)) );
  connect(videoReader, SIGNAL(processedImage(QImage)),
          mainForm, SLOT(updatePlayerUI(QImage)) );
  connect(videoReader, SIGNAL(ready(int)),
          this, SLOT(videoReaderReady(int)) );

  connect(videoReader, SIGNAL (finished()), thread, SLOT (quit())); //
  connect(videoReader, SIGNAL (finished()), videoReader, SLOT (deleteLater())); //
  connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
  thread->start();

  return true;
}

// === =======================================================================

void HiddenVultureApp::videoReaderReady(int delay) {
  // create timer here etc

  controlTimer = new QTimer();
  connect(controlTimer, SIGNAL(timeout()), videoReader, SLOT(nextFrame()));
  controlTimer->setSingleShot(false);
  controlTimer->setInterval(delay);
  controlTimer->start();

}

// === =======================================================================

int HiddenVultureApp::getAppExitCode() const {
  return appExitCode;
}

// === =======================================================================
// === =======================================================================
