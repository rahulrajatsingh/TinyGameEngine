#include "StdAfx.h"
#include "Slider.h"

using namespace GEngine;

Slider::Slider(PlayerSlider slider)
: xPos(0)
, yPos(18) //lets put it in center for now
{
  if(PLAYER_ONE_SLIDER == slider)
  {
    xPos = 1;
  }
  else
  {
    xPos = 79;
  }

  position.lower = yPos;
  position.upper = yPos + SLIDER_LENGTH;

  slider_ = new QuadObject(SLIDER_WIDTH,SLIDER_LENGTH,VERTEX(xPos,yPos,0), COLOR_RED, XY);

  Direct3DInterface::GetInstance().AddObject(slider_);
}

Slider::~Slider(void)
{
}

void Slider::MoveSlider(DirectionSlider direction)
{
  if(direction == SLIDER_GO_UP)
  {
    yPos += 1;
  }
  else
  {
    yPos -= 1;
  }

  position.lower = yPos;
  position.upper = yPos + SLIDER_LENGTH;

  slider_->SetPosition(VERTEX(xPos,yPos,0));
}


SliderPosition Slider::GetPosition()
{
  return position;
}