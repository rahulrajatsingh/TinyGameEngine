#ifndef TYPES_H_
#define TYPES_H_

#include "stdafx.h"

namespace GEngine
{
	//List down the major colors and create constants so that the user dont have to think about the values and all stuff
	enum D3D_COLOR
	{
		COLOR_BLUE,
		COLOR_BLACK,
		COLOR_RED,
    COLOR_PURPLE,
		COLOR_SIZE
	};
	//-----------------------------------------------------------------------------------------------------------------

	typedef struct Vertex
	{
		Vertex(float x = 0, float y = 0, float z = 0)
		{
			this->X = x;
			this->Y = y;
			this->Z = z;
		}

		float X;
		float Y;
		float Z;
	}VERTEX;
	
	enum PLANE
	{
		XY,
		YZ,
		XZ	
	};
}

const float pi = 3.141592f;
#endif