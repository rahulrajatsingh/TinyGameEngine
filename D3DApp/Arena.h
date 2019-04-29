#pragma once
#include "QuadObject.h"
#include "types.h"

const int ARENA_WIDTH = 75;
const int ARENA_LENGTH = 81;

class Arena
  {
  public:
    Arena(void);
    ~Arena(void);   

  private:
    GEngine::QuadObject *arenaLeftBorder;
    GEngine::QuadObject *arenaRightBorder;
    GEngine::QuadObject *arenaTopBorder;
    GEngine::QuadObject *arenaBottomBorder;
    GEngine::QuadObject *arenaNet;
  };
