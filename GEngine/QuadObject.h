#pragma once
#include <d3d9.h>

#include "iobject.h"
#include "Direct3DInterface.h"
#include "InternalTypes.h"

namespace GEngine
{
	const int NUMBER_POINTS = 3;

	class QuadObject : public IObject
	{
	public:
	  QuadObject(unsigned int length, unsigned int width, VERTEX position, D3D_COLOR color, PLANE plane = XY);
	  ~QuadObject(void);
	  
	  int Render();
    void SetPosition(VERTEX position);

	private:
		void PrepareShape();
		
		CUSTOMVERTEX LowerTrianglevertices[NUMBER_POINTS];
		CUSTOMVERTEX UpperTrianglevertices[NUMBER_POINTS];
		IDirect3DVertexBuffer9* quadVertexBuffer;		

		//this will be used to store the vertices and render them
		VOID* vertexBuffer;
    int length;
    int width;
    PLANE plane;
	};
};