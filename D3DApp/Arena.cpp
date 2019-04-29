#include "StdAfx.h"
#include "Arena.h"

using namespace GEngine;

Arena::Arena(void)
  {
    arenaLeftBorder =   new QuadObject(1,ARENA_WIDTH,VERTEX(0,0,0), COLOR_BLUE, XY);
    arenaRightBorder =  new QuadObject(1,ARENA_WIDTH,VERTEX(ARENA_LENGTH - 1,0,0), COLOR_BLUE, XY);
    arenaTopBorder =    new QuadObject(ARENA_LENGTH,1,VERTEX(0,ARENA_WIDTH - 1,0), COLOR_BLUE, XY);
    arenaBottomBorder = new QuadObject(ARENA_LENGTH,1,VERTEX(0,0,0), COLOR_BLUE, XY);
    arenaNet = new QuadObject(1,ARENA_WIDTH,VERTEX((ARENA_LENGTH - 2)/2,0,0), COLOR_BLUE, XY);

    Direct3DInterface::GetInstance().AddObject(arenaLeftBorder);
    Direct3DInterface::GetInstance().AddObject(arenaRightBorder);
    Direct3DInterface::GetInstance().AddObject(arenaTopBorder);
    Direct3DInterface::GetInstance().AddObject(arenaBottomBorder);
    Direct3DInterface::GetInstance().AddObject(arenaNet);
  }

Arena::~Arena(void)
  {
  }