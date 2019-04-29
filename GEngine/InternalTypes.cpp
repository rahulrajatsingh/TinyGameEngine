#include "stdafx.h"
#include "InternalTypes.h"

namespace GEngine
{
	InternalTypes& InternalTypes::GetInstance()
	{
		static InternalTypes instance;

		return instance;
	}

	InternalTypes::InternalTypes()		
	{
		actualColor[COLOR_BLUE] = D3DCOLOR_XRGB(0,0,255);
		actualColor[COLOR_BLACK] = D3DCOLOR_XRGB(0,0,0);
		actualColor[COLOR_RED] = D3DCOLOR_XRGB(255,0,0);
    actualColor[COLOR_PURPLE] = D3DCOLOR_ARGB(255, 255, 0, 255);
	}
}
