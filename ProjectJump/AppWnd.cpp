#include "AppWnd.h"

AppWnd::AppWnd(){

	//A Window starts at NULL
	_hwnd = NULL;
}

HWND AppWnd::createWnd(HINSTANCE hInstance,
				LPCTSTR clsName,
				LPCTSTR wndName,
				int	x,
				int y,
				int width,
				int height,
				HWND	parent,
				DWORD	dStyle,
				DWORD	dXStyle){

					//Attempt to create the window

					RECT wr = {0, 0, width, height};    // set the size, but not the position
					if(!AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE)){ // adjust the size
						// warn or someting
					}
					

					_hwnd = CreateWindowEx(dXStyle, clsName, wndName, dStyle,
						                   x, y, 
										   wr.right - wr.left, 
										   wr.bottom - wr.top, 
										   parent, NULL, 
										   hInstance, NULL);

					if(_hwnd != NULL){ //If everything went well we return our newly created window.
						return _hwnd;
					}

					return NULL; //Something went wrong in CreateWindowEx
}

bool AppWnd::show(int nCmdShow){

	if(ShowWindow(_hwnd, nCmdShow)){ //Try to show and update the window.
		UpdateWindow(_hwnd);	//UpdateWindow returns false if window is empty eg. there is noting to redraw.
		return true;
	}
	else return false;
}

AppWnd::operator HWND(){
	return _hwnd;
}

HWND AppWnd::getWnd(){
	return _hwnd;
}

