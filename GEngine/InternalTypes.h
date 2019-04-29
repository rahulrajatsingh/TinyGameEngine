#ifndef INTERNALTYPES_H_
#define INTERNALTYPES_H_

#include "stdafx.h"
#include <windows.h>
#include <d3d9types.h>
#include <map>
#include "types.h"
#include <d3dx9math.h>
//this file will be used only be the engine and not outside

namespace GEngine
{
	//this is the vertex format we are going to use
	struct CUSTOMVERTEX
	{
		float x, y, z; // The transformed position for the vertex.
		unsigned int color;        // The vertex color.
	};

  struct FONT2DVERTEX 
  { 
    D3DXVECTOR4 p;   
    DWORD color;     
    FLOAT tu, tv; 
  };

	#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)
  #define D3DFVF_FONT2DVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)


	class InternalTypes
	{
	public:
		static InternalTypes& GetInstance();
		std::map<D3D_COLOR,unsigned int> actualColor;

	private:
		InternalTypes();
		InternalTypes(const InternalTypes&);
		InternalTypes& operator=(const InternalTypes&);

		
	};
}
#endif