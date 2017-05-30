#include "MainForm.h"
#include "FiveCatsLogger.h"
#include "VideoPanel.h"
//#include "VideoFrameReader.h"

#include <QAbstractButton>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QSpacerItem>
#include <QVBoxLayout>

#include <Qt> // KeepAspectRatio
#include <QBitmap>
#include <QColor>
#include <QCloseEvent>
#include <QCursor>
#include <QPixmap>

//#include <QDebug>

// ============================================================================

MainForm::MainForm(const QString& ss, FiveCatsLogger* c5p,
                   QWidget *parent) : QWidget(parent) {
  //
  initPlayingOptions();
  playingOptions.filename = ss;

  c5 = c5p;

  prepareUI();
}


// ============================================================================

MainForm::~MainForm() {
  // the MainForm object is parent to all the UI elements, so there is
  // no need to delete them manually
  c5->t(__c5_MN__, "");
//  delete controlTimer ;
}

// ============================================================================

void MainForm::closeEvent(QCloseEvent *) {
  emit gettingClosed();
}

// ============================================================================

QString MainForm::getErrorMessage() const {
  return errorMessage;
}

// ============================================================================

void MainForm::prepareUI() {
  //
  prepareVideoLabel();

  //
  QWidget* sidePanel = prepareUiSidePanel();

  //
  QHBoxLayout* mainHBoxLayout = new QHBoxLayout(this);
  mainHBoxLayout->addWidget(videoLabel,1);
  mainHBoxLayout->addWidget(sidePanel);

  //
  setLayout(mainHBoxLayout);

  //
  setFixedSize(640,480);

  playingOptions.guiFrameHeight = videoLabel->height();
  playingOptions.guiFrameWidth = videoLabel->width();
  c5d(c5, QString("VideoLabel sizes are supposed to be %1x%2")
             .arg(playingOptions.guiFrameWidth).arg(playingOptions.guiFrameHeight)) ;
}

// ============================================================================

QWidget* MainForm::prepareUiSidePanel() {
  QVBoxLayout* sidePanelLayout = new QVBoxLayout();

  //
  playStopButton = new QPushButton();
  playStopButton->setText("Stop");
  connect(playStopButton, SIGNAL(clicked()),
          this, SLOT(onPlayStopButtonClicked()));
  sidePanelLayout->addWidget(playStopButton);

  //
  QWidget* crosshairBox = prepareUiSidePanelCrosshairType();
  sidePanelLayout->addWidget(crosshairBox);

  QCheckBox *showFilenameCheckBox = new QCheckBox("Show Filename");
  showFilenameCheckBox->setChecked(true);
  connect(showFilenameCheckBox, SIGNAL(stateChanged(int)),
          this, SLOT(showFilenameStateChanged(int)) );
  sidePanelLayout->addWidget(showFilenameCheckBox);

  //
  sidePanelLayout->addStretch(1);

  //finally
  QWidget* sidePanel = new QWidget();
  sidePanel->setLayout(sidePanelLayout);
  return sidePanel;
}

// ============================================================================

QWidget* MainForm::prepareUiSidePanelCrosshairType() {
  QGroupBox *groupBox = new QGroupBox("Crosshair Type");

  QRadioButton *radio1 = new QRadioButton("Type 1");
  QRadioButton *radio2 = new QRadioButton("Type 2");
  QRadioButton *radio3 = new QRadioButton("Type 3");

  crosshairTypesRBG = new QButtonGroup(this);
  crosshairTypesRBG->addButton(radio1,0);
  crosshairTypesRBG->addButton(radio2,1);
  crosshairTypesRBG->addButton(radio3,2);

  connect(crosshairTypesRBG,
          SIGNAL(buttonClicked(QAbstractButton*)),
          this,
          SLOT(crosshairTypeChanged(QAbstractButton*)) );

  radio1->setChecked(true);

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(radio1);
  vbox->addWidget(radio2);
  vbox->addWidget(radio3);
  groupBox->setLayout(vbox);

  return groupBox;
}

// ============================================================================

void MainForm::prepareVideoLabel() {
  videoLabel = new VideoPanel(c5);

  videoLabel->setAlignment(Qt::AlignCenter);
  videoLabel->setText("Loading video, please wait ...");

  connect(videoLabel, SIGNAL(squareSizeChanged(int)),
          this, SLOT(selectorSizeChanged(int)) );
  connect(videoLabel, SIGNAL(squarePosChanged(int, int)),
          this, SLOT(selectorPosChanged(int, int)) );
}

// ============================================================================

void MainForm::crosshairTypeChanged(QAbstractButton *)  {
  const int currentSelected = crosshairTypesRBG->checkedId();
  c5->t(__c5_MN__, QString("%1").arg(currentSelected));
  if (playingOptions.crosshairType!=currentSelected) {
    playingOptions.crosshairType = currentSelected;
    emit videoOptionsChanged(playingOptions);
  }
  //qDebug() << "MainForm::crosshairTypeChanged" << currentSelected;
}

// ============================================================================

void MainForm::updatePlayerUI(QImage img) {

  if (img.isNull()) {
    return;
  }


//  const QSize videoSize = videoLabel->size();
//  const QSize imageSize = img.size();
//  if  ( (videoSize.width()!=imageSize.width()) ||
//        (videoSize.height()!=imageSize.height()) ) {
////    videoLabel->resize(imageSize);
//    c5d(c5, QString("Bad Sizes %1x%2 vs %3x%4")
//               .arg(videoSize.width()).arg(videoSize.height())
//               .arg(imageSize.width()).arg(imageSize.height()) );
//  }

  videoLabel->setPixmap(QPixmap::fromImage(img)) ;
  //  videoLabel->setPixmap(QPixmap::fromImage(img).scaled(videoLabel->size().width(), videoLabel->size().height(),
  //                        Qt::KeepAspectRatio, Qt::FastTransformation));
  //}
}

// ============================================================================

void MainForm::initPlayingOptions() {
  playingOptions.playing = true;
//  playingOptions.filename = videoFileName;

  playingOptions.showFilename = true;
  playingOptions.crosshairType = 0;

  playingOptions.selectorSize = 16 ;
  playingOptions.selectorX = 0;
  playingOptions.selectorY = 0;

  // this is not set here
  //playingOptions.guiFrameHeight
}

// ============================================================================

PlayingOptions MainForm::getPlayingOptions() const{
  return playingOptions ;
}

// ============================================================================

void MainForm::startPlaying() {
  if (playingOptions.playing) {
    return;
  }

  playingOptions.playing = true;
  emit videoOptionsChanged(playingOptions);
  playStopButton->setText("Stop");
}

// ============================================================================

void MainForm::stopPlaying() {
  if (!playingOptions.playing) {
    return;
  }

  playingOptions.playing = false;
  emit videoOptionsChanged(playingOptions);

  playStopButton->setText("Start");
}

// ============================================================================

void MainForm::onPlayStopButtonClicked() {
  if (playingOptions.playing) {
    stopPlaying();
  }
  else {
    startPlaying();
  }
}

// ============================================================================

void MainForm::showFilenameStateChanged(int state)  {
  c5->t(__c5_MN__, QString("%1").arg(state));
  const bool newState = (state != 0) ;
  if (newState != playingOptions.showFilename) {
    playingOptions.showFilename = newState ;
    emit videoOptionsChanged(playingOptions);
  }
}

// ============================================================================

void MainForm::selectorSizeChanged(int newss) {
  c5->f(__c5_MN__, QString("%1").arg(newss));

  if (newss!=playingOptions.selectorSize) {
    playingOptions.selectorSize = newss;
    emit videoOptionsChanged(playingOptions);
  }
}

// ============================================================================

void MainForm::selectorPosChanged(int x, int y) {
  c5->f(__c5_MN__, QString("(%1, %2)").arg(x).arg(y));

  if ( (x!=playingOptions.selectorX) || (y!=playingOptions.selectorY) ) {
    playingOptions.selectorX = x;
    playingOptions.selectorY = y;
    emit videoOptionsChanged(playingOptions);
  }
}

// ============================================================================

void MainForm::showEvent(QShowEvent *) {
  playingOptions.guiFrameHeight = videoLabel->height();
  playingOptions.guiFrameWidth = videoLabel->width();
  c5t(c5, QString("Showed videoLabel sizes are supposed to be %1x%2")
             .arg(playingOptions.guiFrameWidth).arg(playingOptions.guiFrameHeight)) ;
}

// ============================================================================

void MainForm::videoReaderError(QString message) {
  videoLabel->setText(message);
}

// ============================================================================
