// D3DApp.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "D3DApp.h"
#include "PhysicsEngine.h"

#define MAX_LOADSTRING 100

using namespace GEngine;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void AddBall();

//hwnd to the current window
HWND hWnd;

//global object of direct3d interface
Direct3DInterface &d3dInterface = Direct3DInterface::GetInstance();
Camera camera = Camera::GetCamera();
PhysicsEngine *physics = 0;
bool canMoveBall = false;

void CreatePhysicsEngine()
{
  physics = new PhysicsEngine(hWnd);
}

void CleanUp()
{  
  if(physics != 0)
  {
    delete physics;
  }  
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_D3DAPP, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_D3DAPP));

  //Here lets try to initialze the d3d stuff
  int result = d3dInterface.InitializeD3D();

  d3dInterface.CreateDevice(hWnd);

	d3dInterface.AddCamera(&camera);
  
  CreatePhysicsEngine();

  canMoveBall = true;

  // Main message loop:
  while (GetMessage(&msg, NULL, 0, 0))
  {
	  if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	  {
		  TranslateMessage(&msg);
		  DispatchMessage(&msg);
      /*if(true == canMoveBall)
      {
        physics->MoveBall();
      }*/
      d3dInterface.Render();
	  }
  }
  


  CleanUp();

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_D3DAPP));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_D3DAPP);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

  VERTEX currVer;
    VERTEX vertexToSet;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
    case ID_FILE_CONTROLS:
      MessageBox(0, L"Player 1:\n\tMove Up = W\n\tMove Down = S\n\tShoot ball = D \nPlayer 2:\n\tMove Up = UP\n\tMove Down = DOWN\n\tShoot ball = LEFT", L"Controls", 0);
      break;
    case ID_FILE_RESETGAME:
      MessageBox(0, L"Starting a new game", L"Controls", 0);
      physics->ResetGame();
      break;
		
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
		
    
		case WM_KEYDOWN:
		{
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			switch (wmId)
			{
			case VK_UP:
				physics->MoveSlider(PLAYER_TWO_SLIDER, SLIDER_GO_UP);
				break;
				
			case VK_DOWN:
				physics->MoveSlider(PLAYER_TWO_SLIDER, SLIDER_GO_DOWN);
				break;

        case VK_LEFT:
				  if(physics->GetAttachedSlider() == PLAYER_TWO_SLIDER)
          {
            physics->StartBallMovement();
          }
        break;
			
      case 'D':
			case 'd':
				if(true == canMoveBall)
        {
          if(physics->GetAttachedSlider() == PLAYER_ONE_SLIDER)
          {
            physics->StartBallMovement();
          }
        }
				break;
			case 'S':
			case 's':
				physics->MoveSlider(PLAYER_ONE_SLIDER, SLIDER_GO_DOWN);
				break;
				
			case 'W':
			case 'w':
				physics->MoveSlider(PLAYER_ONE_SLIDER, SLIDER_GO_UP);
				break;
				
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
				break;
			}
		}		
		break;
		
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here... 
    
		ValidateRect( hWnd, NULL );

		EndPaint(hWnd, &ps);
		break;		

  case WM_REDRAW:
    d3dInterface.Render();
    break;
	
	case WM_DESTROY:		
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
