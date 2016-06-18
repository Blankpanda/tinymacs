#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#include "debugLogger.h"

#define dbg(str) OutputDebugStringA(str) 

void CallDebugConsole(void) {

     
     CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
     int consoleHandleR, consoleHandleW;
     long stdioHandle;
     
     FILE *fptr;
     
     SetConsoleTitle("Debug Console.");

     AllocConsole();
     DrawMenuBar(GetConsoleWindow());

     GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo );

     stdioHandle = (long)GetStdHandle( STD_INPUT_HANDLE );
     consoleHandleR = _open_osfhandle( stdioHandle, _O_TEXT );
     fptr = _fdopen( consoleHandleR, "r" );
     *stdin = *fptr;
     setvbuf( stdin, NULL, _IONBF, 0 );

     stdioHandle = (long) GetStdHandle( STD_OUTPUT_HANDLE );
     consoleHandleW = _open_osfhandle( stdioHandle, _O_TEXT );
     fptr = _fdopen( consoleHandleW, "w" );
     *stdout = *fptr;
     setvbuf( stdout, NULL, _IONBF, 0 );

     stdioHandle = (long)GetStdHandle( STD_ERROR_HANDLE );
     *stderr = *fptr;
     setvbuf( stderr, NULL, _IONBF, 0 );

     LPCTSTR message = NULL;     	 	  
}

// Displays a message box with specified parameters
void DebugMbox(HWND WindowHandle, LPCTSTR text, LPCSTR caption, UINT type, bool logDebug)
{
     int temp = MessageBox(WindowHandle, text, caption, type);

     if (logDebug) {
	  dbg(text);
	  WriteDebugMessage( (char *)&text);
     }
}

LPCTSTR GetDebugMessage()
{
     return "";
}

// TODO: Timestamp
void WriteDebugMessage(char* message)
{
     printf("%s", message);
}
