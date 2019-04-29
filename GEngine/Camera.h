#pragma once
#include <d3dx9math.h>
#include "types.h"

namespace GEngine
{
	class Camera
	{
	public:
		static Camera& GetCamera(void);
		void SetCamera();
		~Camera(void);
		
		void ShiftRight();
		void ShiftLeft();
		void ShiftUp();
		void ShiftDown();
		void ShiftForward();
		void ShiftBackward();

	private:
		Camera(void);
		void SetCameraLocation();
		
		void UpdateLookAtPosition();
		D3DXMATRIX matView;
		
		VERTEX cameraPosition; 
		VERTEX LookAtPosition;
	};
}
