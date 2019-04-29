#include "StdAfx.h"
#include "Ball.h"

const VERTEX INITIAL_BALL_POSITION = VERTEX(10,10,0);

Ball::Ball(void)
: ball_(0)
, ballPosition_(INITIAL_BALL_POSITION)
{
  ball_ = new CircleObject(ballPosition_, 1, COLOR_RED, XY);

  Direct3DInterface::GetInstance().AddObject(ball_);
}

Ball::~Ball(void)
{
  
}

void Ball::SetPosition(VERTEX pos)
{
  ballPosition_ = pos;
  ball_->SetPosition(ballPosition_);
}

VERTEX Ball::GetPosition()
{
  return ballPosition_;
}

