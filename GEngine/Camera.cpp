#include "StdAfx.h"
#include "Camera.h"
#include "Direct3dInterface.h"

namespace GEngine
{
	const float MOVEMENT_IN_PIXELS = 0.2f;
	
	Camera& Camera::GetCamera(void)
	{
		static Camera camera;
		return camera;
	}

	Camera::Camera(void)
	{
		//default location of the camera
		cameraPosition.X = 41.0;
		cameraPosition.Y = 37.0;
		cameraPosition.Z = -100.0;			
		
		UpdateLookAtPosition();
	}

	Camera::~Camera(void)
	{
		
	}

	void Camera::SetCamera()
	{
		SetCameraLocation();
	}

	void Camera::SetCameraLocation()
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixRotationY( &matWorld, 0.0f );
    Direct3DInterface::GetInstance().pDevice->SetTransform( D3DTS_WORLD, &matWorld );

		D3DXVECTOR3 vEyePt( cameraPosition.X, cameraPosition.Y,cameraPosition.Z );
    D3DXVECTOR3 vLookatPt( LookAtPosition.X, LookAtPosition.Y, LookAtPosition.Z );
    
    //For now we are always keeping y as up vector
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
		Direct3DInterface::GetInstance().pDevice->SetTransform( D3DTS_VIEW, &matView );	

		D3DXMATRIX matProj;
		D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
		Direct3DInterface::GetInstance().pDevice->SetTransform( D3DTS_PROJECTION, &matProj );
	}
	
	void Camera::UpdateLookAtPosition()
	{
		//default position we will look at	
		LookAtPosition.X = cameraPosition.X;
		LookAtPosition.Y = cameraPosition.Y;
		LookAtPosition.Z = cameraPosition.Z + 1000;				
	}
	
	void Camera::ShiftRight()
	{
		cameraPosition.X += MOVEMENT_IN_PIXELS;
		
		UpdateLookAtPosition();
	}
	
	void Camera::ShiftLeft()
	{
		cameraPosition.X -= MOVEMENT_IN_PIXELS;
		
		UpdateLookAtPosition();
	}
	
	void Camera::ShiftUp()
	{
		cameraPosition.Y += MOVEMENT_IN_PIXELS;
		
		UpdateLookAtPosition();
	}
	
	void Camera::ShiftDown()
	{
		cameraPosition.Y -= MOVEMENT_IN_PIXELS;
		
		UpdateLookAtPosition();
	}
	
	void Camera::ShiftForward()
	{
		cameraPosition.Z += MOVEMENT_IN_PIXELS;
		
		UpdateLookAtPosition();
	}
	
	void Camera::ShiftBackward()
	{
		cameraPosition.Z -= MOVEMENT_IN_PIXELS;
		
		UpdateLookAtPosition();
	}
}
