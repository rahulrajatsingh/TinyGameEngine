#include "StdAfx.h"
#include "PhysicsEngine.h"
#include <windows.h>
#include <string>

using namespace GEngine;

const float theta = pi/4.0f;
const int WIN_POINTS = 10;

PhysicsEngine::PhysicsEngine(HWND handleToMainWindow)
: arena_(0)
, ball_(0)
, sliderOne_(0)
, sliderTwo_(0)
, incX(true)
, incY(true)
, isThreadCreated(false)
, ballThread(0)
, handleToMainWindow_(handleToMainWindow)
, isBallAttachedToSlider_(true)
, attachedSlider(PLAYER_ONE_SLIDER)
, text_P1(0)
, text_P2(0)
, p1Score(0)
, p2Score(0)
{
  CreateArena();
  AddSliders();
  CreateBall();

  ResetGame();
}

void PhysicsEngine::ResetGame()
{
  ResetBall(PLAYER_ONE_SLIDER);
  p1Score = 0;
  p2Score = 0;

  wchar_t newOne[5];
  wsprintf(newOne, L"%d",p1Score);

  std::wstring newScoreOne(newOne);
  text_P1->SetText(newScoreOne);

  wsprintf(newOne, L"%d",p2Score);
  std::wstring newScoreTwo(newOne);
  text_P2->SetText(newScoreTwo);
}
void PhysicsEngine::UpdateScore(PlayerSlider slider)
{
  int num = 0;
	wchar_t newOne[5];
  
  if(slider == PLAYER_ONE_SLIDER)
  {
    ++p1Score;
    wsprintf(newOne, L"%d",p1Score);

    std::wstring newScore(newOne);
    text_P1->SetText(newScore);
    if(WIN_POINTS == p1Score)
    {
      MessageBox(0,L"Player 1 wins", L"Winner", 0);
      ResetGame();
    }
  }
  else
  {
    ++p2Score;
    wsprintf(newOne, L"%d",p2Score);
    std::wstring newScore(newOne);
    text_P2->SetText(newScore);
    if(WIN_POINTS == p2Score)
    {
      MessageBox(0,L"Player 2 wins", L"Winner", 0);
      ResetGame();
    }
  }
}

PhysicsEngine::~PhysicsEngine(void)
{
  if(ballThread != 0)
  {
    CloseHandle(ballThread);
    ballThread = 0;
  }
  if(arena_ != 0)
  {
    delete arena_;
  }

  if(sliderOne_ != 0)
  {
    delete sliderOne_;
  }
  if(sliderTwo_ != 0)
  {
    delete sliderTwo_;
  }
  if(ball_ != 0)
  {
    delete ball_;
  }
  if(text_P1 != 0)
  {
    delete text_P1;
  }
  if(text_P2 != 0)
  {
    delete text_P2;
  }
}

void PhysicsEngine::CreateArena()
{
  arena_ = new Arena();
  text_P1 = new TextObject(32,20,32,COLOR_PURPLE);
  text_P1->SetPosition(VERTEX(25,20,0));
  text_P1->SetText(L"0");
  Direct3DInterface::GetInstance().AddObject(text_P1);

  text_P2 = new TextObject(32,20,32,COLOR_PURPLE);
  text_P2->SetPosition(VERTEX(1130,20,0));
  text_P2->SetText(L"0");
  Direct3DInterface::GetInstance().AddObject(text_P2);
}

void PhysicsEngine::AddSliders()
{
  sliderOne_ = new Slider(PlayerSlider::PLAYER_ONE_SLIDER);
  sliderTwo_ = new Slider(PlayerSlider::PLAYER_TWO_SLIDER);
}

void PhysicsEngine::CreateBall()
{
  ball_ = new Ball();
}


bool PhysicsEngine::IsBallInArena()
{
  bool retVal = false;
  VERTEX ballPos = ball_->GetPosition();

  if( (ballPos.X > 0) && (ballPos.X < 82) && (ballPos.Y > 2) && (ballPos.Y < 73) )
  {
    retVal = true;
  }
  if(ballPos.X <= 4)
  {
    //Check for player 1 Paddle collition here
    if(true == IsSliderPresent(PLAYER_ONE_SLIDER))
    {
      ball_->SetPosition(VERTEX(ballPos.X + 1, ballPos.Y, 0));
      incX = true;
    }
  }
  if(ballPos.X >= 77)
  {
    //check for player 2 paddle collision here
    if(true == IsSliderPresent(PLAYER_TWO_SLIDER))
    {
      ball_->SetPosition(VERTEX(ballPos.X - 1, ballPos.Y, 0));
      incX = false;
    }
  }
  //simce ball is out of arena bring it back
  if(false == retVal)
  {
    if(ballPos.X <= 0)
    {
      //DECLARE WINNER HERE
      ball_->SetPosition(VERTEX(ballPos.X + 1, ballPos.Y, 0));
      isBallAttachedToSlider_ = true;
      ResetBall(PLAYER_TWO_SLIDER);
      UpdateScore(PLAYER_TWO_SLIDER);
      incX = true;
    }
    if(ballPos.X >= 82)
    {
      //DECLARE WINNER HERE
      ball_->SetPosition(VERTEX(ballPos.X - 1, ballPos.Y, 0));
      isBallAttachedToSlider_ = true;
      ResetBall(PLAYER_ONE_SLIDER);
      UpdateScore(PLAYER_ONE_SLIDER);
      incX = false;
    }    
    if(ballPos.Y <= 2)
    {
      //RELECT HERE
      ball_->SetPosition(VERTEX(ballPos.X, ballPos.Y+1, 0));
      incY = true;
    }
    if(ballPos.Y >= 73)
    {
      //REFLECT HERE
      ball_->SetPosition(VERTEX(ballPos.X, ballPos.Y-1, 0));
      incY = false;
    }
  }
  return retVal;
}

void PhysicsEngine::MoveBall()
{
  if(true == IsBallInArena())
  {
    VERTEX ballPos = ball_->GetPosition();
    if(true == incX)
    {
      ballPos.X += theta*2;
    }
    else
    {
      ballPos.X -= theta*2;
    }
    if(true == incY)
    {
      ballPos.Y += theta*2;
    }
    else
    {
      ballPos.Y -= theta*2;
    }
    ball_->SetPosition(ballPos);
  }
}

DWORD WINAPI ThreadProc( LPVOID lpParam )
{
  PhysicsEngine *physics_ = (PhysicsEngine*)lpParam;

  if(physics_->IsThreadCreated() == true)
  {
    while(1)
    {
      if(true == physics_->IsBallAttachedToSlider())
      {
        break;
      }
      physics_->MoveBall();
      ::PostMessage(physics_->GetMainWindowHandle(), WM_REDRAW, 0, 0);
      
      Sleep(75);
    }
  }

  return 1;
}

void PhysicsEngine::StartBallMovement()
{
  if(0 == ballThread)
  {
    ballThread = CreateThread( NULL, 0, 
             ThreadProc, (LPVOID)this, 0, NULL);  
    if ( ballThread != NULL)
    {
      //The thread creation failed
      isThreadCreated = true;
      isBallAttachedToSlider_ = false;
      attachedSlider = PLAYER_NONE;
    }    
  }
}

bool PhysicsEngine::IsThreadCreated()
{
  return isThreadCreated;
}

HWND PhysicsEngine::GetMainWindowHandle()
{
  return handleToMainWindow_;
}

bool PhysicsEngine::IsSliderPresent(PlayerSlider slider)
{
  Slider *currSlider = 0;
  if(slider == PLAYER_ONE_SLIDER)
  {
    currSlider = sliderOne_;
  }
  else
  {
    currSlider = sliderTwo_;
  }
  
  SliderPosition sliderPos = currSlider->GetPosition();
  VERTEX ballPos = ball_->GetPosition();

  if((ballPos.Y > sliderPos.lower) && (ballPos.Y < sliderPos.upper))
    return true;
  else 
    return false;
}


void PhysicsEngine::ResetBall(PlayerSlider slider)
{
  //Stop the ball movement
  if(ballThread != 0)
  {
    CloseHandle(ballThread);
    ballThread = 0;
  }
  
  SliderPosition sliderPos;
  VERTEX ballPos;

  if(slider == PLAYER_ONE_SLIDER)
  {
    sliderPos = sliderOne_->GetPosition();
    ballPos.X = 3;
    ballPos.Y = (sliderPos.lower + sliderPos.upper)/2.0f;
  }
  else
  {
    sliderPos = sliderTwo_->GetPosition();
    ballPos.X = 78;
    ballPos.Y = (sliderPos.lower + sliderPos.upper)/2.0f;
  }
  isBallAttachedToSlider_ = true;
  attachedSlider = slider;

  ball_->SetPosition(ballPos);
}

bool PhysicsEngine::IsBallAttachedToSlider()
{
  return isBallAttachedToSlider_;
}

bool PhysicsEngine::IsSliderInBounds(PlayerSlider player, DirectionSlider direction)
{
  Slider *currentSlider = 0;
  switch(player)
  {
  case PLAYER_ONE_SLIDER:
    currentSlider = sliderOne_;
    break;
  case PLAYER_TWO_SLIDER:
    currentSlider = sliderTwo_;
    break;
  }

  SliderPosition pos;
  if(0 != currentSlider)
  {
    pos = currentSlider->GetPosition();

    if(direction == SLIDER_GO_UP)
    {
      if(pos.lower >= (ARENA_WIDTH - SLIDER_LENGTH - 1))
      {
        return false;
      }
    }
    else
    {
      if(pos.lower <= 1)
      {
        return false;
      }
    }
  }
  return true;
}

void PhysicsEngine::MoveSlider(PlayerSlider player, DirectionSlider direction)
{
  Slider *currentSlider = 0;

  switch(player)
  {
  case PLAYER_ONE_SLIDER:
    currentSlider = sliderOne_;
    break;
  case PLAYER_TWO_SLIDER:
    currentSlider = sliderTwo_;
    break;
  }

  if(0 != currentSlider)
  {
    if(true == IsSliderInBounds(player,direction))
    {
      currentSlider->MoveSlider(direction);
    }
  }

  if(isBallAttachedToSlider_ == true)
  {
    if(player == attachedSlider)
    {
      if(direction == SLIDER_GO_UP)
      {
        VERTEX ballPos = ball_->GetPosition();
        ball_->SetPosition(VERTEX(ballPos.X, ballPos.Y+1, ballPos.Z));
      }
      else
      {
         VERTEX ballPos = ball_->GetPosition();
         ball_->SetPosition(VERTEX(ballPos.X, ballPos.Y-1, ballPos.Z));
      }
    }
  }
}

PlayerSlider PhysicsEngine::GetAttachedSlider()
{
  return attachedSlider;
}