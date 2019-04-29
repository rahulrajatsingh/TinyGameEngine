#pragma once
#include <d3d9.h>

#include "iobject.h"
#include "Direct3DInterface.h"
#include "InternalTypes.h"

namespace GEngine
{
  const int NUMBER_POINTS_CIRCLE = 192;

  class CircleObject : public IObject
  {
  public:
    CircleObject(VERTEX center, int radius, D3D_COLOR color, PLANE plane);
    ~CircleObject(void);

    void SetPosition(VERTEX position);
    int Render();

  private:
    void PrepareShape();

    VERTEX center_;
    int radius_;
    PLANE plane_;
    D3D_COLOR color_;

    CUSTOMVERTEX circleVertices[NUMBER_POINTS_CIRCLE+1];
    IDirect3DVertexBuffer9* circleVertexBuffer;	
    VOID* vertexBuffer;
  };
}