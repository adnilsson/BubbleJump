#include "WndCls.h"

WndCls::WndCls(HINSTANCE hInstance, LPCTSTR clsName, WNDPROC wndProc, LPCTSTR menuName){
	ZeroMemory(&_wc,sizeof(WNDCLASSEX));

	//From parameters
	_wc.hInstance		= hInstance;
	_wc.lpszClassName	= clsName;
	_wc.lpfnWndProc		= wndProc;
	_wc.lpszMenuName	= menuName;
	_wc.cbSize			= sizeof(WNDCLASSEX);

	//Other / default values
	_wc.style			= CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	_wc.hCursor			= LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	_wc.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	_wc.hIconSm			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	_wc.hbrBackground	= (HBRUSH)COLOR_WINDOW;
	_wc.cbClsExtra		= 0;
	_wc.cbWndExtra		= 0;
	
}

bool WndCls::registerClsEX(){

	if(RegisterClassEx(&_wc)){ //Try to register the class
		return true;
	}
	return false; //failed to register class
}

		
