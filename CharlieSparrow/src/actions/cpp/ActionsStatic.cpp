#include "ActionsStatic.h"
#include "DoNothingAction.h"

// === =======================================================================

ActionBasic* ActionsStatic::createActionPerformer(const QString& actionCode, QObject* parent) {
  ActionBasic* result = 0 ;

  if (actionCode == "dna" ) {
     result = new DoNothingAction(parent);
  }

  return result;
}

// === =======================================================================

QList<QPair<QString, QString> > ActionsStatic::commandLineOptions() {
  QList<QPair<QString, QString> > result ;

  result.append(DoNothingAction::commandLineOptions());

  return result ;
}

// === =======================================================================

QString ActionsStatic::avilableActionCodes() {
  return "dna";
}

// === =======================================================================
