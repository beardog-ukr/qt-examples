#ifndef __VideoPanel_h__
#define __VideoPanel_h__

#include <QLabel>
class FiveCatsLogger;

// ===========================================================================

class VideoPanel: public QLabel {
  Q_OBJECT
public:
  VideoPanel(FiveCatsLogger*c5, QWidget* parent =0) ;
  virtual ~VideoPanel();

signals:
  void squareSizeChanged(int newSize);
  void squarePosChanged(int newX, int newY);

protected: //reimplemented
  virtual void wheelEvent(QWheelEvent *event);
  virtual void mouseMoveEvent(QMouseEvent *event);
  virtual void mousePressEvent(QMouseEvent *event) ;

protected:
  int squareSize;
  int minSquareSize;
  int maxSquareSize;
  int squareSizeIncrement ;

  FiveCatsLogger* c5;

};

#endif
