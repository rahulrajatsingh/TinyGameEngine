#pragma once
#include "QuadObject.h"
#include "types.h"

enum PlayerSlider
{
  PLAYER_ONE_SLIDER,
  PLAYER_TWO_SLIDER,
  PLAYER_NONE,
};

enum DirectionSlider
{
  SLIDER_GO_UP,
  SLIDER_GO_DOWN,
};

struct SliderPosition
{
  float lower;
  float upper;
};


const int SLIDER_WIDTH = 1;
const int SLIDER_LENGTH = 10;

class Slider
{
public:
  Slider(PlayerSlider slider);
  ~Slider(void);

  void MoveSlider(DirectionSlider direction);
  SliderPosition GetPosition();

private:
  GEngine::QuadObject *slider_;

  int xPos;
  int yPos;

  SliderPosition position;

};
