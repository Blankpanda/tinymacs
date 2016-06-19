#ifndef _debugLogger
#define _debugLogger

#include "debugLogger.h"

/* Debug types*/
#define DEBUG_NOTIFY        0x0001
#define DEBUG_WARNING       0x0002
#define DEBUG_ERROR         0x0003


/* header definitions */
void CallDebugConsole();

void DebugMbox(HWND, LPCTSTR, LPCTSTR, UINT, bool, char*, int);

void WriteDebugMessage(int, char*, char*);

LPCTSTR GetDebugMessage();

#endif
