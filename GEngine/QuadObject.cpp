#include "StdAfx.h"
#include "QuadObject.h"

namespace GEngine
{
	QuadObject::QuadObject(unsigned int length, unsigned int width, VERTEX position, D3D_COLOR color, PLANE plane)
	{
    this->length = length;
    this->width = width;
    this->plane = plane;
		LowerTrianglevertices[1].color = LowerTrianglevertices[2].color = LowerTrianglevertices[0].color = UpperTrianglevertices[1].color = UpperTrianglevertices[2].color = UpperTrianglevertices[0].color = InternalTypes::GetInstance().actualColor[color];
						
		SetPosition(position);
	}

	QuadObject::~QuadObject(void)
	{

	}

	void QuadObject::PrepareShape()
	{
		CUSTOMVERTEX rectanglevertices[6];
		for(int count = 0; count < 3; ++count)
		{
			rectanglevertices[count] = LowerTrianglevertices[count];
		}
		for(int count = 3; count < 6; ++count)
		{
			rectanglevertices[count] = UpperTrianglevertices[count - 3];
		}
		if( SUCCEEDED( Direct3DInterface::GetInstance().pDevice->CreateVertexBuffer( 6*sizeof(CUSTOMVERTEX),
         0 /* Usage */, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &quadVertexBuffer , 0) ) )
		{			
			if( SUCCEEDED( quadVertexBuffer->Lock( 0, sizeof(rectanglevertices), (void**)&vertexBuffer, 0 ) ) )
			{
				memcpy( vertexBuffer, rectanglevertices, sizeof(rectanglevertices) );

				quadVertexBuffer->Unlock();
			}			
		}
	}

	int QuadObject::Render()
	{
    if(quadVertexBuffer != 0)
    {
		  if( SUCCEEDED( Direct3DInterface::GetInstance().pDevice->SetStreamSource( 0, quadVertexBuffer, 0, sizeof(CUSTOMVERTEX) ) ) )
		  {
		  if(SUCCEEDED (Direct3DInterface::GetInstance().pDevice->SetFVF( D3DFVF_CUSTOMVERTEX ) ) )
			  {
			  if(SUCCEEDED( Direct3DInterface::GetInstance().pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 ) ))
				  {
					  //will think later how can i handle the return values to optimize the behavior
					  return 1;
				  }
			  }
		  }
    }
		return -1;
	}	

  void QuadObject::SetPosition(VERTEX position)
  {
    float xFactor = 0.0f;
		float yFactor = 0.0f;
		float zFactor = 0.0f;
		
		switch(plane)
		{
		case XY:
			xFactor = length;
			yFactor = width;
		break;
		
		case YZ:
			yFactor = length;
			zFactor = width;
		break;
		
		case XZ:
			xFactor = length;
			zFactor = width;
		break;		
		}
		
		//plot the initial vertices
		LowerTrianglevertices[0].x = position.X;
		LowerTrianglevertices[0].y = position.Y;
		LowerTrianglevertices[0].z = position.Z;
		
		if(YZ == plane)
		{
			LowerTrianglevertices[1].x = position.X;
			LowerTrianglevertices[1].y = position.Y + yFactor;
			
			UpperTrianglevertices[1].x = position.X + xFactor;
			UpperTrianglevertices[1].y = position.Y;
		}
		else
		{
			LowerTrianglevertices[1].x = position.X + xFactor;
			LowerTrianglevertices[1].y = position.Y;

			UpperTrianglevertices[1].x = position.X;
			UpperTrianglevertices[1].y = position.Y + yFactor;
		}
		
		LowerTrianglevertices[1].z = position.Z;
		UpperTrianglevertices[1].z = position.Z + zFactor;
		
		LowerTrianglevertices[2].x = position.X + xFactor;
		LowerTrianglevertices[2].y = position.Y + yFactor;
		LowerTrianglevertices[2].z = position.Z + zFactor;
		
		UpperTrianglevertices[0] = LowerTrianglevertices[2];
		UpperTrianglevertices[2] = LowerTrianglevertices[0];

    PrepareShape();
  }
}