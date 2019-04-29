#include "StdAfx.h"
#include "Direct3DInterface.h"
#include "InternalTypes.h"

namespace GEngine
{
	Direct3DInterface& Direct3DInterface::GetInstance()
	{
		static Direct3DInterface instance;

		return instance;
	}


  Direct3DInterface::Direct3DInterface(void)
  : g_pD3D(0)
  , pDevice(0)
	, isCameraPresent(false)
  {
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
  }

  Direct3DInterface::~Direct3DInterface(void)
  {
    if( 0 != g_pD3D)
    {
      g_pD3D->Release();
      g_pD3D = 0;
    }

    if(0 != pDevice)
    {
      pDevice->Release();
      pDevice = 0;
    }
  }

  int Direct3DInterface::InitializeD3D()
  {
    //first we need to create a d3d device pointer

    if( D3D_OK != (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
    {
      return -1;
    }
    return 1;
  }

  int Direct3DInterface::CreateDevice(HWND hWnd)
  {
    if(0 == g_pD3D)
    {
      MessageBox(0,L"Direct3D not initialized successfully so not attempting to create device", 0,0);
      return -1;
    }
    else
    {
      //lets use these for now but they can be externalized too
      D3DPRESENT_PARAMETERS d3dpp;
			ZeroMemory( &d3dpp, sizeof(d3dpp) );
			d3dpp.Windowed = TRUE;
	    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		  d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

			if( SUCCEEDED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                    D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                        &d3dpp, &pDevice ) ) )
      {
			  // Turn off culling, so we see the front and back of the triangle
				pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

				// Turn off D3D lighting, since we are providing our own vertex colors
				pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );  
				
				// Turn on the zbuffer
				//g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );     
      }
			else
				{
					MessageBox(0,L"Direct3D create device failed", 0,0);
					return -1;
				}

      return 1;
    }
  }

  int Direct3DInterface::ClearScreen(D3D_COLOR color)
  {
    if( 0 == pDevice)
    {
      return -1;
    }
  
    if(D3D_OK != pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, InternalTypes::GetInstance().actualColor[color], 1.0f, 0 ))
    {
      return -1;
    }
      
    return 1;
  }

  int Direct3DInterface::Render()
  {
		HRESULT hr = E_FAIL;
    if( 0 == pDevice)
    {
      return -1;
    }

		ClearScreen(COLOR_BLACK);

    // Begin the scene.
    hr = pDevice->BeginScene();

		//check if camera is thr or not
		if(true == isCameraPresent)
		{
			camera->SetCamera();
		}
    // Rendering of scene objects happens here.
		for(unsigned int count = 0; count < sprites.size(); ++count)
		{
			sprites.at(count)->Render();
		}
    
    // End the scene.
    hr = pDevice->EndScene();

    hr = pDevice->Present( 0, 0, 0, 0 );

    return -1;
  }

	void Direct3DInterface::AddObject(IObject* sprite)
	{
		sprites.push_back(sprite);
	}

  void Direct3DInterface::RemoveObject(IObject*sprite)
	{
		//ohhh, how can i remove the sprit, damn, think later
	}

	void Direct3DInterface::AddCamera(Camera* cam)
	{
		camera = cam;

		isCameraPresent = true;
	}
}
