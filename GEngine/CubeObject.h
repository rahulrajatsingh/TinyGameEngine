#pragma once
#include "QuadObject.h"

namespace GEngine
{
	class CubeObject : public IObject 
	{
	public:
		CubeObject(float length, float height, float width, VERTEX position, D3D_COLOR color);
		~CubeObject(void);
		
		int Render();
				
	private:
		void PrepareShape();
		
		QuadObject faceFront;
		QuadObject faceLeft;
		QuadObject faceRight;
		QuadObject faceBack;
		QuadObject faceTop;
		QuadObject faceBottom;		
	};
}
