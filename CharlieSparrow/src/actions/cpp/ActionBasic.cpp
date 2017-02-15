#include "ActionBasic.h"

//=== ========================================================================

ActionBasic::ActionBasic(QObject* parent)
            :QObject(parent) {
  errorMessage = "";
}

//=== ========================================================================

ActionBasic::~ActionBasic() {
  //ntdh
}

//=== ========================================================================

QString ActionBasic::getErrorMessage() const {
  return errorMessage;
}

//=== ========================================================================
