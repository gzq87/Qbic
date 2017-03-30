#include "util.h"

static DWORD start_clock_count;

DWORD Get_Clock()
{
	return GetTickCount();
}

DWORD Start_Clock()
{
	return (start_clock_count = Get_Clock());
}

DWORD Wait_Clock(DWORD count)
{
	while ((Get_Clock() - start_clock_count) < count);
	return(Get_Clock());
}