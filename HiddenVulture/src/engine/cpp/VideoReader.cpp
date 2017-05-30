#include "VideoReader.h"
#include "FiveCatsLogger.h"

//#include <QDebug>

#include <QImage>
#include <QFile>
#include <QFileInfo>

#include <cmath>

#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"

// ============================================================================
// ============================================================================

VideoReader::VideoReader(const PlayingOptions& po, QObject *parent) : QObject(parent) {
 playingOptions = po;
 c5 =0;
}

// ============================================================================

VideoReader::~VideoReader() {
//  qDebug() << "VideoFrameReader::~VideoFrameReader()" ;
  //note, everything should be destroyed in shutDOwn()
  delete c5;
  c5 =0;
}

// ============================================================================

void VideoReader::shutDown() {
  //qDebug() << "VideoFrameReader::shutDown()" ;
  capture.release();
  emit finished();
}

// ============================================================================

void VideoReader::getReady() {
  c5 = new FiveCatsLogger(FiveCatsLogger::Debug);

  QString em = "";
  QFileInfo finfo(playingOptions.filename);
  if ( !finfo.exists() ) {
    em = QString("File \"%1\" not found").arg(playingOptions.filename);
  }
  if ( em.isEmpty() && ( !finfo.isFile() ) ){
    em = QString("\"%1\" is not a file").arg(playingOptions.filename);
  }
  if (!em.isEmpty()) {
    c5c(c5, em );
    emit error(em);
    return;
  }

  capture.open(playingOptions.filename.toLatin1().toStdString());
  if (capture.isOpened())  {
    frameRate = (int) capture.get(CV_CAP_PROP_FPS);
    const int delay = (1000/frameRate);
    emit ready(delay);
  }
  else {
    em =  QString("Failed to open file (%1)").arg(playingOptions.filename) ;
    c5c(c5, em);
    emit error(em);
  }
}

// ============================================================================
//for drawing examples see
//  http://opencvexamples.blogspot.com/2013/10/basic-drawing-examples.html
void VideoReader::nextFrame() {
  //
  if (!playingOptions.playing) {
    return;
  }

  Mat inputFrame;
  if (!capture.read(inputFrame)) {
    emit finished() ;
    return;
  }

  int gfw = inputFrame.cols;
  int gfh = inputFrame.rows;
  float scaleFactor =1;
  if ( (inputFrame.cols>playingOptions.guiFrameWidth) ||
       (inputFrame.rows>playingOptions.guiFrameHeight) ) {
    if (playingOptions.guiFrameWidth > playingOptions.guiFrameHeight) {
      gfw = playingOptions.guiFrameWidth ;
      scaleFactor = (playingOptions.guiFrameWidth*1.0)/inputFrame.cols ;
      gfh = (int)round(inputFrame.rows*scaleFactor) ;
    }
    else {
      gfh = playingOptions.guiFrameHeight ;
      scaleFactor = (playingOptions.guiFrameHeight*1.0)/inputFrame.rows ;
      gfw = (int)round(inputFrame.cols*scaleFactor) ;
    }
  }

//  c5d(c5, QString("Calculated scale from %1x%2 to %3x%4 (%5)")
//                 .arg(inputFrame.cols).arg(inputFrame.rows)
//                 .arg(playingOptions.guiFrameWidth).arg(playingOptions.guiFrameHeight)
//                 .arg(scaleFactor) ) ;

  resize(inputFrame, frame, Size(gfw, gfh) );
  drawCornerCircles();

  switch (playingOptions.crosshairType) {
  case 0 :
    drawCrosshairType1(scaleFactor);
    break;
  case 1 :
    drawCrosshairType2(scaleFactor);
    break;
  case 2 :
    drawCrosshairType3(scaleFactor);
    break;
  }

  //
  drawSelectorRectangle(scaleFactor);
  drawFilename(scaleFactor);

  Mat fullFrame = Mat::zeros(playingOptions.guiFrameWidth, playingOptions.guiFrameHeight, CV_8UC3);  
  const int topShift = (playingOptions.guiFrameHeight-frame.rows) /2 ;
  const int lowShift = playingOptions.guiFrameHeight - topShift - frame.rows;  
//  copyMakeBorder(frame, fullFrame, topShift, lowShift, 0,0,BORDER_REPLICATE );
  copyMakeBorder(frame, fullFrame, topShift, lowShift, 0,0,BORDER_CONSTANT, Scalar( 128, 128, 0 ) );
  frame =  fullFrame;

  if (frame.channels()== 3){
    cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
    img = QImage((const unsigned char*)(RGBframe.data),
                 RGBframe.cols,RGBframe.rows, RGBframe.step, QImage::Format_RGB888);
    }
    else {
      img = QImage((const unsigned char*)(frame.data),
                   frame.cols,frame.rows,QImage::Format_Indexed8);
    }

  emit processedImage(img);
}

// ============================================================================

void VideoReader::drawSelectorRectangle(const float& scaleFactor) {
  int sx = playingOptions.selectorX ;// (int)round(playingOptions.selectorX*scaleFactor) ;
  int sy = playingOptions.selectorY ;//(int)round(playingOptions.selectorY*scaleFactor) ;
  const int ss = playingOptions.selectorSize;//(int)round(playingOptions.selectorSize*scaleFactor) ;


  if ( (sx+ss)>=frame.cols) {
    sx= frame.cols - ss;
  }
  if ((sy+ss)>=frame.rows) {
    sy = frame.rows -ss ;
  }

  rectangle(frame,
            Point( sx, sy ), Point( sx+ss, sy+ss) ,
            Scalar( 128, 0, 0 ), 4, 8 );
}

// ============================================================================

void VideoReader::drawFilename(const float& scaleFactor) {
  if (!playingOptions.showFilename) {
    return ;
  }

  const int sx = (int)round(10*scaleFactor) ;
  const int sy = (int)round(30*scaleFactor) ;

  putText(frame,
          playingOptions.filename.toLatin1().toStdString(),
          Point(sx,sy), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,200,200), 2);
}

// ============================================================================

void VideoReader::drawCrosshairType1(const float& scaleFactor) {
  const int centerX = frame.cols /2 ;
  const int centerY = frame.rows /2 ;
  int crossRadius = round(30*scaleFactor);
  if (crossRadius>=centerX) {
    crossRadius = centerX/2;
  }
  if (crossRadius>=centerY) {
    crossRadius = centerY/2;
  }

  line( frame,
        Point( centerX-crossRadius, centerY ),
        Point( centerX+crossRadius, centerY),
        Scalar( 0, 0, 0 ),  4, 8 );

  line( frame,
        Point( centerX, centerY+crossRadius),
        Point( centerX, centerY-crossRadius ),
        Scalar( 0, 0, 0 ),  4, 8 );
}

// ============================================================================

void VideoReader::drawCrosshairType2(const float& scaleFactor) {
  const int centerX = frame.cols /2 ;
  const int centerY = frame.rows /2 ;
  int crossRadius = round(30*scaleFactor);
  if (crossRadius>=centerX) {
    crossRadius = centerX/2;
  }
  if (crossRadius>=centerY) {
    crossRadius = centerY/2;
  }

  line( frame,
        Point( centerX-crossRadius, centerY ),
        Point( centerX+crossRadius, centerY),
        Scalar( 0, 0, 0 ),  4, 8 );

  line( frame,
        Point( centerX, centerY+crossRadius),
        Point( centerX, centerY-crossRadius ),
        Scalar( 0, 0, 0 ),  4, 8 );

  circle( frame,
          Point( centerX, centerY ), 24.0, Scalar( 0, 0, 0 ), 4, 8 );
}

// ============================================================================

void VideoReader::drawCrosshairType3(const float& scaleFactor) {
  const int centerX = frame.cols /2 ;
  const int centerY = frame.rows /2 ;
  int crossRadius = round(30*scaleFactor);
  if (crossRadius>=centerX) {
    crossRadius = centerX/2;
  }
  if (crossRadius>=centerY) {
    crossRadius = centerY/2;
  }

  line( frame,
        Point( centerX-crossRadius, centerY-crossRadius ),
        Point( centerX+crossRadius, centerY+crossRadius),
        Scalar( 0, 0, 0 ),  4, 8 );

  line( frame,
        Point( centerX-crossRadius, centerY+crossRadius),
        Point( centerX+crossRadius, centerY-crossRadius ),
        Scalar( 0, 0, 0 ),  4, 8 );
}

// ============================================================================

void VideoReader::drawCornerCircles() {
  const int bd = 30; //distance between circle center and frame border

  circle( frame, Point( bd, bd ), 24.0, Scalar( 0, 0, 0 ), 4, 8 );
  circle( frame, Point( frame.cols-bd, bd ), 24.0, Scalar( 0, 0, 0 ), 4, 8 );
  circle( frame, Point( bd, frame.rows-bd ), 24.0, Scalar( 0, 0, 0 ), 4, 8 );
  circle( frame, Point( frame.cols - bd, frame.rows - bd ), 24.0, Scalar( 0, 0, 0 ), 4, 8 );
}

// ============================================================================

void VideoReader::processNewOptions(const PlayingOptions& newOptions) {
  playingOptions = newOptions ;
}

// ============================================================================

