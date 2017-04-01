#pragma once

#include <windows.h>

#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif // _UNICODE

DWORD Get_Clock();
DWORD Start_Clock();
DWORD Wait_Clock(DWORD count);