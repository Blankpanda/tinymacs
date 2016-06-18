#include <windows.h>

#include "debugLogger.h"
HINSTANCE hInst;

LRESULT CALLBACK MainWindowCallBack(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK MainWindowCallBack(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC DeviceContext = BeginPaint(hWnd, &ps);
	LRESULT Result = 0;

	switch(Message)
	{
	case WM_SIZE:
	{	
	  WriteDebugMessage("WM_SIZE\n");
	} break;
	
	case WM_PAINT:
	{	   
	     int X = ps.rcPaint.left;
	     int Y = ps.rcPaint.top;
	     LONG Height = ps.rcPaint.bottom - ps.rcPaint.top;
	     LONG Width = ps.rcPaint.right - ps.rcPaint.left;
	     PatBlt(DeviceContext,X, Y, Width, Height, WHITENESS);
	     EndPaint(hWnd, &ps);	    
	} break;
	
	case WM_CLOSE:
	{
	  WriteDebugMessage("WM_Close\n");
	} break;
	    
	case WM_DESTROY:
	{
	     PostQuitMessage(0);     
	} break;

	default:
	{
	     Result = DefWindowProc(hWnd, Message, wParam, lParam);
	     return DefWindowProc(hWnd, Message, wParam, lParam);	
	} break;

	}

	return Result;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
{
     WNDCLASS WindowClass = {0};
     
  
     
     WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;    
     WindowClass.lpfnWndProc = MainWindowCallBack;
     WindowClass.cbClsExtra = 0;
     WindowClass.cbWndExtra = 0;
     WindowClass.hInstance = hInstance;
     WindowClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
     WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
     WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
     WindowClass.lpszMenuName = NULL;
     WindowClass.lpszClassName = "editor";
 
     
     if(RegisterClass(&WindowClass)) {

	   HWND WindowHandle = CreateWindowEx(
	       0,
	       WindowClass.lpszClassName,
	       "Testing",
	       WS_OVERLAPPEDWINDOW,
	       CW_USEDEFAULT,
	       CW_USEDEFAULT,
	       CW_USEDEFAULT,
	       CW_USEDEFAULT,
	       0,
	       0,
	       hInstance,
	       0
	       );
	   

	   ShowWindow(WindowHandle,nCmdShow);
	   UpdateWindow(WindowHandle);
	   CallDebugConsole();
	  if(WindowHandle) {
	       MSG msg;
	       while(GetMessage(&msg,NULL,0,0)) {
	  		 TranslateMessage(&msg);
	  		 DispatchMessage(&msg);
	       }
	  }
	  else
	  {
	    DebugMbox(WindowHandle, "RegisterClass Failed!.", 0, 0 ,1);
	  }
     }
     else
     {
       //TODO: DEBUG LOG
     }
}


