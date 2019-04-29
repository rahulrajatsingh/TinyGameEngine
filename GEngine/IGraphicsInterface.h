#pragma once
#include <windows.h>
#include "types.h"

namespace GEngine
{
  class IGraphicsInterface
  {
  public:
    IGraphicsInterface(void);
    ~IGraphicsInterface(void);

    int InitializeD3D();
    int CreateDevice(HWND hWnd);
    int ClearScreen(D3D_COLOR color);
    int Render();
  };
}