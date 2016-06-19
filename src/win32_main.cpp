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
	     POINT mouseCursor;
	     GetCursorPos(&mouseCursor);
	     
	     BeginDeferWindowPos(0);
	     DeferWindowPos(0 ,hWnd, 0, ps.rcPaint.left, ps.rcPaint.right, mouseCursor.x , mouseCursor.y ,0);
	     EndDeferWindowPos(0);

	     // int bytes = GetModuleFileName(NULL, __FILE__, sizeof(__FILE__));
	     // WriteDebugMessage(DEBUG_NOTIFY, "win32_main.cpp",(char*)bytes);
	} break;
	case WM_PAINT:
	{	   
	     int X = ps.rcPaint.left;
	     int Y = ps.rcPaint.top;
	     LONG Height = ps.rcPaint.bottom - ps.rcPaint.top;
	     LONG Width = ps.rcPaint.right - ps.rcPaint.left;
	     PatBlt(DeviceContext,X, Y, Width, Height, WHITENESS|BLACKNESS);
	     EndPaint(hWnd, &ps);	    
	} break;
	
	case WM_CLOSE:
	{	 
	     PostQuitMessage(0);
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
     WNDCLASS WindowClass;
         
     WindowClass.style = 0;    
     WindowClass.lpfnWndProc = MainWindowCallBack;
     WindowClass.cbClsExtra = 0;
     WindowClass.cbWndExtra = 0;
     WindowClass.hInstance = hInstance;
     WindowClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
     WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
     WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
     WindowClass.lpszMenuName = 0;
     WindowClass.lpszClassName = "editor";
      
     if(RegisterClass(&WindowClass)) {

	   HWND WindowHandle = CreateWindowEx(
	       0,
	       WindowClass.lpszClassName,
	       "editor",
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
	       WriteDebugMessage(DEBUG_ERROR, "win32_main.cpp","WindowHandle Returned NULL.");
	  }
     }
     else
     {
	  WriteDebugMessage(DEBUG_ERROR, "win32_main.cpp", "RegisterClass failed.");
     }
}


