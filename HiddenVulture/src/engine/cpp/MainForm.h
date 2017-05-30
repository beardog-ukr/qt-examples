#ifndef __MainForm__
#define __MainForm__

#include <QString>

#include <QWidget>
class QAbstractButton;
class QButtonGroup;
class QLabel;
class QPushButton;
class QTimer;

#include "PlayingOptions.h"
class FiveCatsLogger;
class VideoPanel;

// ============================================================================

class MainForm : public QWidget{
  Q_OBJECT
public:
  explicit MainForm(const QString& videoFileName, FiveCatsLogger* c5,
                    QWidget *parent = 0);
  ~MainForm();

  QString getErrorMessage() const;
  PlayingOptions getPlayingOptions() const;

private slots:
  // video handling slots
  void updatePlayerUI(QImage img); //Display video frame in player UI
  void videoReaderError(QString message);
  // other GUI elements slots
  void onPlayStopButtonClicked();
  void showFilenameStateChanged(int state) ;
  void crosshairTypeChanged(QAbstractButton *button) ;
  void selectorSizeChanged(int newss);
  void selectorPosChanged(int x, int y);

signals:
  void gettingClosed();
  void videoOptionsChanged(PlayingOptions newOptions);

protected:
  void closeEvent(QCloseEvent *event); // reimplements QWidget
  void showEvent(QShowEvent *event) ;// reimplements QWidget

  QString errorMessage;

  void prepareUI();
  QWidget* prepareUiSidePanel();
  QWidget* prepareUiSidePanelCrosshairType();
  void prepareVideoLabel();
  QButtonGroup* crosshairTypesRBG ;

//  QTimer* controlTimer;
  VideoPanel* videoLabel;

//  VideoFrameReaderOptions vfrOptions;
//  VideoFrameReader* vfr;
//  void startVideoThread();
  PlayingOptions playingOptions;
  void initPlayingOptions();

  QPushButton* playStopButton;
  void startPlaying();
  void stopPlaying();

  FiveCatsLogger* c5;
};



#endif
