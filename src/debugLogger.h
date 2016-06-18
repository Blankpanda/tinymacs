#ifndef _debugLogger
#define _debugLogger

// TODO: Clean up dependencies


#include "debugLogger.h"

/* header definitions */
void CallDebugConsole();
void DebugMbox(HWND, LPCTSTR, LPCTSTR, UINT, bool);
void WriteDebugMessage(char* message);
LPCTSTR GetDebugMessage();

#endif
