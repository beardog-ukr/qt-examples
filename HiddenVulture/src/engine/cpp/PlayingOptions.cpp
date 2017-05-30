#include "PlayingOptions.h"
//#include <QDebug>

// ============================================================================
// ============================================================================

PlayingOptions::PlayingOptions()
{
}

PlayingOptions::PlayingOptions(const PlayingOptions &other)
{
  playing = other.playing ;
  filename = other.filename;

  showFilename = other.showFilename;
  crosshairType = other.crosshairType;

  selectorSize = other.selectorSize ;
  selectorX = other.selectorX;
  selectorY = other.selectorY;

  guiFrameWidth = other.guiFrameWidth;
  guiFrameHeight = other.guiFrameHeight;
}

PlayingOptions::~PlayingOptions()
{
}

// ============================================================================
// ============================================================================
