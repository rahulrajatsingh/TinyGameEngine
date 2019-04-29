#include "StdAfx.h"
#include "CircleObject.h"
#include <math.h>

namespace GEngine
{
  CircleObject::CircleObject(VERTEX position, int radius, D3D_COLOR color, PLANE plane)
  : center_(position)
  , radius_(radius)
  , plane_(plane)
  , color_(color)
  {    
    for(int count = 0; count <= NUMBER_POINTS_CIRCLE; ++count)
		{
			circleVertices[count].color = InternalTypes::GetInstance().actualColor[color];
		}
    SetPosition(position);
  }

  CircleObject::~CircleObject(void)
  {
  }

  void CircleObject::SetPosition(VERTEX position)
  {
    center_ = position;
    circleVertices[0].x = center_.X;
    circleVertices[0].y = center_.Y;
    circleVertices[0].z = center_.Z;
    float theta = 0.0f;

    for ( int count = 1; count <= (NUMBER_POINTS_CIRCLE); ++count)
    {
      circleVertices[count].x = center_.X + (cos(float(theta))*radius_);
      circleVertices[count].y = center_.Y + (sin(float(theta))*radius_);
      circleVertices[count].z = 0;

      theta += (2.0f*pi/NUMBER_POINTS_CIRCLE);
    }

    PrepareShape();
  }

  void CircleObject::PrepareShape()
  {
    CUSTOMVERTEX circlePoints[NUMBER_POINTS_CIRCLE+1];
		for(int count = 0; count <= NUMBER_POINTS_CIRCLE; ++count)
		{
			circlePoints[count] = circleVertices[count];
		}
		
		if( SUCCEEDED( Direct3DInterface::GetInstance().pDevice->CreateVertexBuffer( (NUMBER_POINTS_CIRCLE+1)*sizeof(CUSTOMVERTEX),
         0 /* Usage */, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &circleVertexBuffer , 0) ) )
		{			
			if( SUCCEEDED( circleVertexBuffer->Lock( 0, sizeof(circlePoints), (void**)&vertexBuffer, 0 ) ) )
			{
				memcpy( vertexBuffer, circlePoints, sizeof(circlePoints) );

				circleVertexBuffer->Unlock();
			}			
		}
  }

  int CircleObject::Render()
  {
    if(circleVertexBuffer != 0)
    {
      if( SUCCEEDED( Direct3DInterface::GetInstance().pDevice->SetStreamSource( 0, circleVertexBuffer, 0, sizeof(CUSTOMVERTEX) ) ) )
		  {
		  if(SUCCEEDED (Direct3DInterface::GetInstance().pDevice->SetFVF( D3DFVF_CUSTOMVERTEX ) ) )
			  {
			  if(SUCCEEDED( Direct3DInterface::GetInstance().pDevice->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, NUMBER_POINTS_CIRCLE - 1 ) ))
				  {
					  //will think later how can i handle the return values to optimize the behavior
					  return 1;
				  }
			  }
		  }
    }
		return -1;
  }
}