#include "VideoPanel.h"
#include "FiveCatsLogger.h"
//

#include <Qt>
#include <QMouseEvent>
#include <QPoint>
#include <QWheelEvent>

// ===========================================================================

VideoPanel::VideoPanel(FiveCatsLogger* c5p, QWidget* parent) :QLabel(parent) {
  c5 = c5p ;

  setStyleSheet(QString("QLabel { "
                        "  background-color : rgb(0,0,0) ;"
                        "  color: yellow;"
                        "  font : bold"
                        "}"
                        ));

  squareSize = 16;
  minSquareSize = 16;
  maxSquareSize = 64;
  squareSizeIncrement =16;

  setCursor(Qt::BlankCursor);
  setMouseTracking(true);
}

// ===========================================================================

VideoPanel::~VideoPanel() {
//
}

// ===========================================================================

void VideoPanel::wheelEvent(QWheelEvent *event) {
  int newSS = squareSize;

  const QPoint ad = event->angleDelta();

  if (ad.y()>0) {
    newSS = squareSize+squareSizeIncrement;
    if (newSS>maxSquareSize) {
      newSS = squareSize ;
    }
  }
  else if (ad.y()<0) {
    newSS = squareSize-squareSizeIncrement;
    if (newSS<minSquareSize) {
      newSS = squareSize ;
    }
  }

  if (newSS != squareSize) {
    squareSize = newSS;
    emit squareSizeChanged(squareSize);
  }
}

// ===========================================================================

void VideoPanel::mouseMoveEvent(QMouseEvent *event) {
  const QPoint np = event->pos();
//  qDebug() << "VideoPanel::mouseMoveEvent"  << np.x() << np.y() ;
  emit squarePosChanged(np.x(), np.y());
}

// ===========================================================================

void VideoPanel::mousePressEvent(QMouseEvent *event) {
  const QPoint np = event->pos();
  c5f(c5, QString("Selector: (%1, %1) X (%3, %4) ")
           .arg(np.x()).arg(np.y()).arg(np.x()+squareSize).arg(np.y()+squareSize) );
}

// ===========================================================================
