#ifndef __PlayingOptions_h__
#define __PlayingOptions_h__

#include <QString>

// ===========================================================================

class PlayingOptions {

public:
  PlayingOptions();
  PlayingOptions(const PlayingOptions &other);
  ~PlayingOptions();

  bool playing;
  QString filename;

  bool showFilename;
  int crosshairType;

  int selectorSize;
  int selectorX;//top left selector X
  int selectorY;//top left selector Y

  int guiFrameWidth;
  int guiFrameHeight;
};

//Q_DECLARE_METATYPE(PlayingOptions)

// ===========================================================================

#endif // __PlayingOptions_h__
