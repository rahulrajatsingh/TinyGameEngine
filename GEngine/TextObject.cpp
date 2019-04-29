#include "StdAfx.h"
#include "TextObject.h"

using namespace std;

namespace GEngine
{
  TextObject::TextObject(int length, int width, int fontSize, D3D_COLOR color)
  : font_(0)
  , text_(L"")
  , length_(length)
  , width_(width)
  , color_(InternalTypes::GetInstance().actualColor[color])
  , fontSize_(fontSize)
  , position_(VERTEX(0,0,0))
  {
    HDC hdc = ::CreateCompatibleDC(NULL);
    int logicalUnitHeight = -MulDiv(fontSize_, GetDeviceCaps(hdc, LOGPIXELSY), 72);

    HFONT font = ::CreateFont( logicalUnitHeight, 0, 0, 0, FW_DONTCARE, false, false, false, 
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));

    // Create a D3DX font object
    D3DXCreateFont( Direct3DInterface::GetInstance().pDevice, font, &font_ );
    DeleteObject( font );
  }

  TextObject::~TextObject(void)
  {
    if(font_ != 0)
    {
      font_->Release();
    }    
  }

  void TextObject::SetPosition(VERTEX pos)
  {
    position_ = pos;
  }

  void TextObject::SetText(wstring text)
  {
    text_ = text;
  }

  int TextObject::Render()
  {
    // Create a rectangle to indicate where on the screen it should be drawn
    RECT rc;
    SetRect( &rc, position_.X, position_.Y + width_, position_.X + length_, position_.Y );
    font_->Begin();
    if(0 != font_->DrawText( text_.c_str(), -1, &rc, 
        DT_SINGLELINE, color_ ))
      {
        font_->End();
        return 1;
      }
    return -1;
  }


  void TextObject::PrepareShape()
  {
    //Damn i have nothing to prepare here
  }
}