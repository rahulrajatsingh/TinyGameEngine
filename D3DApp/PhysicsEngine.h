#pragma once
#include "ball.h"
#include "Arena.h"
#include "Slider.h"
#include "textobject.h"

#define WM_REDRAW WM_USER + 1

class PhysicsEngine
  {
  public:
    PhysicsEngine(HWND handleToMainWindow);
    ~PhysicsEngine(void);
    bool IsBallInArena();
    void MoveBall();
    void StartBallMovement();
    bool IsThreadCreated();
    HWND GetMainWindowHandle();
    bool IsSliderPresent(PlayerSlider slider);
    void ResetBall(PlayerSlider slider);
    bool IsBallAttachedToSlider();
    bool IsSliderInBounds(PlayerSlider player, DirectionSlider direction);
    void MoveSlider(PlayerSlider player, DirectionSlider direction);
    PlayerSlider GetAttachedSlider();
    void ResetGame();

  private:
    void UpdateScore(PlayerSlider slider);
    void PhysicsEngine::CreateBall();
    void PhysicsEngine::AddSliders();
    void PhysicsEngine::CreateArena();
    Arena *arena_;
    Ball *ball_;
    Slider *sliderOne_;
    Slider *sliderTwo_;
    bool incX;
    bool incY;
    bool isThreadCreated;
    HANDLE ballThread;
    HWND handleToMainWindow_;
    bool isBallAttachedToSlider_;
    PlayerSlider attachedSlider;
    TextObject *text_P1;
    TextObject *text_P2;
    int p1Score;
    int p2Score;
  };
