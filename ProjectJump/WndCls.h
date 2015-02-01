#pragma once
#include <Windows.h>
#include "resource.h"
#include <windowsx.h>

//Object that fills and registers a WNDCLASSEX struct.
class WndCls{

public:
	//Fill out the window class/struct
	WndCls(HINSTANCE hInstance, LPCTSTR clsName, WNDPROC wndProc, LPCTSTR menuName = NULL);
	

	bool registerClsEX();

private:
	WNDCLASSEX _wc;
};

