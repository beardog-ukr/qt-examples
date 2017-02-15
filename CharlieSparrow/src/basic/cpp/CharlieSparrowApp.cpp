#include "CharlieSparrowApp.h"
#include "ActionBasic.h"
#include "ActionsStatic.h"
//#include "DoNothingAction.h"

#include <QCommandLineParser>
#include <QCoreApplication>
#include <QTimer>

#include <QDebug>
// === =======================================================================
// === =======================================================================

CharlieSparrowApp::CharlieSparrowApp(QObject* parent)
             :QObject(parent){
  startupTimer = 0;
  actionPerformer = 0;
}

// === =======================================================================

CharlieSparrowApp::~CharlieSparrowApp() {
  delete startupTimer;
  delete actionPerformer;
}

// === =======================================================================

bool CharlieSparrowApp::processCommandLine() {
  bool result = true;
  QMap<QString, QString> options;

  QCommandLineParser parser;
  parser.setApplicationDescription("CharlieSparrow boilerplate Qt application");
  parser.addHelpOption();
  QCoreApplication::setApplicationVersion("0.0.01");
  parser.addVersionOption();

  // command line options
  QCommandLineOption actionOption("action");
  actionOption.setDescription("Some action to perform.");
  actionOption.setValueName("action");
  parser.addOption(actionOption);

  const QList<QPair<QString, QString> > aclo = ActionsStatic::commandLineOptions();
  QList<QPair<QString, QString> >::const_iterator acloi = aclo.constBegin() ;
  for ( ; acloi!= aclo.constEnd(); acloi++) {
    parser.addOption(QCommandLineOption(acloi->first, acloi->second, acloi->first));
  }

  // c5->initCommandLineParser(parser);

  // Process the actual command line arguments given by the user
  QCoreApplication* ca = QCoreApplication::instance();
  parser.process(*ca);
  QList<QPair<QString, QString> > optionsToProcess;
  const QStringList clo = parser.optionNames() ;
  for (QStringList::const_iterator cloi=clo.constBegin(); cloi!=clo.constEnd(); cloi++) {
    QPair<QString, QString> p;
    p.first = *cloi;
    p.second = parser.value(*cloi) ;
    optionsToProcess.append(p);
  }

  // c5->loadCommandLineParser(parser);
  QString actionStr = parser.value(actionOption);

  actionPerformer = ActionsStatic::createActionPerformer(actionStr) ;
  if (actionPerformer) {
     result = actionPerformer->loadCommandLineOptions(optionsToProcess);
  }
  else {
     qDebug() << parser.helpText();
     result = false ;
     appExitCode = 1;
  }

  return result;
}

// === =======================================================================

bool CharlieSparrowApp::prepareToStart() {
  startupTimer = new QTimer(this) ;
  startupTimer->setSingleShot(true);
  connect(startupTimer, SIGNAL(timeout()),this, SLOT(startEveryting()) );
  startupTimer->start(600);
  qDebug() << "Started all" ;
  return true;
}

// === =======================================================================

void CharlieSparrowApp::startEveryting() {
  delete startupTimer;
  startupTimer =0;

  connect(actionPerformer, SIGNAL(actionDone()), this, SLOT(processActionResult()));
  connect(actionPerformer, SIGNAL(actionFailure()), this, SLOT(processActionFailure()));

  bool started = actionPerformer->startAction() ;
  if (!started) {
     qDebug() << "ERROR: at start: " + actionPerformer->getErrorMessage() ;
     delete actionPerformer;
     actionPerformer = 0;
   }

   qDebug() << "App started action" << started ;
}

// === =======================================================================

void CharlieSparrowApp::processActionResult() {
  qDebug() << "Action success" ;
  const QString em = actionPerformer->getErrorMessage();
  if (!em.isEmpty()) {
    qDebug() << "Action finished successfully, but with error message: " << em;
    QCoreApplication::exit(1);
  }

  QCoreApplication::exit(0);
}

// === =======================================================================

void CharlieSparrowApp::processActionFailure() {
  qDebug() << "Action failed";

  const QString em = actionPerformer->getErrorMessage();
  if (em.isEmpty()) {
    qDebug() << "ERROR: action failed for unknown reason" ;
  }
  else {
    qDebug() <<  em ;
  }

  QCoreApplication::exit(1);
}

// === =======================================================================

int CharlieSparrowApp::getAppExitCode() const {
  return appExitCode;
}

// === =======================================================================
// === =======================================================================
