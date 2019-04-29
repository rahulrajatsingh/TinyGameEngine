#pragma once
#include<vector>
#include <d3d9.h>

#include "IGraphicsInterface.h"
#include "iobject.h"
#include "camera.h"

namespace GEngine
{
  class Direct3DInterface : public IGraphicsInterface
  {
  public:
		static Direct3DInterface& GetInstance();

		~Direct3DInterface(void);

    int InitializeD3D();
    int CreateDevice(HWND hWnd);
    int ClearScreen(D3D_COLOR color);
    int Render();

    void AddObject(IObject*);
    void RemoveObject(IObject*);
		void AddCamera(Camera*);

  private:
		Direct3DInterface(void);
		Direct3DInterface(const Direct3DInterface&);
		Direct3DInterface& operator=(const Direct3DInterface&);

    LPDIRECT3D9 g_pD3D;
    LPDIRECT3DDEVICE9 pDevice;
    D3DPRESENT_PARAMETERS d3dpp; 

    std::vector<IObject*> sprites;

		friend class QuadObject;    
		friend class Camera;  
    friend class CircleObject;
    friend class TextObject;

		bool isCameraPresent;
		Camera* camera;
  };
}