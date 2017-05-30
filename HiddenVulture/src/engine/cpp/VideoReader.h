#ifndef __VideoReader_h__
#define __VideoReader_h__

#include <QImage>
#include <QString>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class FiveCatsLogger;
#include "PlayingOptions.h"

using namespace cv;

// ===========================================================================
// The class in based on http://codingexodus.blogspot.com/2012/12/working-with-video-using-opencv-and-qt.html
// should also check https://stackoverflow.com/questions/21246766/how-to-efficiently-display-opencv-video-in-qt
// another thing to try http://develnoter.blogspot.com/2012/05/integrating-opencv-in-qt-gui.html

class VideoReader : public QObject {
 Q_OBJECT

protected:
  Mat frame;
//  Mat scaledFrame;
  int frameRate;
  VideoCapture capture;
  Mat RGBframe;
  QImage img;

  PlayingOptions playingOptions;

  void drawCrosshairType1(const float& scaleFactor);
  void drawCrosshairType2(const float& scaleFactor);
  void drawCrosshairType3(const float& scaleFactor);

  void drawCornerCircles();
  void drawSelectorRectangle(const float& scaleFactor);
  void drawFilename(const float& scaleFactor) ;

  FiveCatsLogger* c5;

signals:
  //Signal to output frame to be displayed
  void processedImage(const QImage &image);
  void finished();
  void ready(int delay);
  void error(const QString msg) ;

public slots:
  void getReady();
  void nextFrame();
  void shutDown();
  void processNewOptions(const PlayingOptions& newOptions);

public:
  VideoReader(const PlayingOptions& po, QObject *parent = 0);
  virtual ~VideoReader();

//  bool setVideoFileName(const QString& filename);
//  int getDelay() ;
};

#endif
