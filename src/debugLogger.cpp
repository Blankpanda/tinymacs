#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#include "debugLogger.h"

#define dbg(str) OutputDebugStringA(str)

/* IDEAS
    FreeConsole(void)
    option structure
    debugmessage structure ( so I dont have to type out a super long message)
    investigate __FILE__
*/
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
void DebugMbox(HWND WindowHandle, LPCTSTR text, LPCSTR caption, UINT type, bool logDebug,  char* file, int DEBUG_MESSAGE)
{
     int temp = MessageBox(WindowHandle, text, caption, type);

     if (logDebug) {
	  dbg(text);
	  WriteDebugMessage(DEBUG_MESSAGE,file,(char*)&text);
     }
}

LPCTSTR GetDebugMessage()
{
     return "";
}

// TODO: Timestamp, Automate the file feature
void WriteDebugMessage(int DEBUG_MESSAGE, char* file, char* message)
{
     char * DebugString = "";
     // I hate how emacs organzies switch statementsn
     switch (DEBUG_MESSAGE) {
     case DEBUG_NOTIFY: {
	  DebugString = "[Notice]";
	  break;
     }
     case DEBUG_WARNING: {
	  DebugString = "[WARNING]";
	  break;
     }
     case DEBUG_ERROR: {
	  DebugString = "[ERROR]";
	  break;
     }
     default: {
	  DebugString = "";
	  break;
     }
     }

     printf("%s file=%s %s.\n", DebugString, file, message);
}
