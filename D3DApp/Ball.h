#pragma once
#include "circleObject.h"
#include "types.h"

using namespace GEngine;

class Ball
{
public:
  Ball(void);
  ~Ball(void);

  void SetPosition(VERTEX pos);
  VERTEX GetPosition();
  
private:
  CircleObject *ball_;
  VERTEX ballPosition_;  
};
