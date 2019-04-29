#pragma once
#include <d3d9.h>

#include "iobject.h"
#include "Direct3DInterface.h"
#include "InternalTypes.h"
#include <string>

namespace GEngine
{
  class TextObject : public IObject
  {
  public:
    TextObject(int length, int width, int fontSize, D3D_COLOR color);
    ~TextObject(void);

    // The text position will always be in pixels and depends on size of screen, so 
    // never get confused by the coordinates given to other 3d objects and 2d text
    // Dirty but what can i do, i m mixing GDI with D3D. will think a little about it later
    void SetPosition(VERTEX pos);
    int Render();
    void SetText(std::wstring text);
    void PrepareShape();

  private:
    ID3DXFont *font_;
    std::wstring text_;
    D3DCOLOR color_;
    int length_;
    int width_;
    int fontSize_; 
    VERTEX position_;
  };
}