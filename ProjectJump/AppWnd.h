#pragma once
#include <Windows.h>
#include <windowsx.h>

class AppWnd{
public:

	AppWnd();

	HWND createWnd(HINSTANCE hInstance,
				LPCTSTR clsName,
				LPCTSTR wndName,
				int	x	= CW_USEDEFAULT, //If no x value is provided, then x = CW_USEDEFAULT
				int y	= CW_USEDEFAULT,
				int width = CW_USEDEFAULT,     //client width (excluding width of borders)
				int height = CW_USEDEFAULT,    //client height
				HWND	parent = NULL,
				DWORD	dStyle = WS_OVERLAPPEDWINDOW,
				DWORD	dXStyle = NULL);

	bool show(int nCmdShwo = SW_SHOWNORMAL);

	operator HWND();
	HWND getWnd();

protected:
	HWND _hwnd;


};