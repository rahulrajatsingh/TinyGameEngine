#include "StdAfx.h"
#include "CubeObject.h"

namespace GEngine
{
	CubeObject::CubeObject(float length, float height, float width, VERTEX position, D3D_COLOR color)
	: faceFront(length, height,position,COLOR_RED, XY)
	,	faceLeft(height,width , position, COLOR_RED, YZ)
	,	faceRight(height, width, VERTEX(position.X + length, position.Y,position.Z), COLOR_RED, YZ)
	,	faceBack(length, height, VERTEX(position.X, position.Y,position.Z + width), COLOR_RED, XY)
	,	faceTop(length, width,VERTEX(position.X , position.Y + height,position.Z),COLOR_RED, XZ)
	,	faceBottom(length, width,position,COLOR_RED, XZ)
	{
	}

	CubeObject::~CubeObject(void)
	{
	}
	
	void CubeObject::PrepareShape()
	{
	
	
	}
	
	int CubeObject::Render()
	{
		faceFront.Render();
		faceLeft.Render();
		faceRight.Render();
		faceBack.Render();
		faceTop.Render();
		faceBottom.Render();
		
		return 1;
	}
}
