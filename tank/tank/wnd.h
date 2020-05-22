#pragma once

#include<windows.h>
#include<tchar.h>

#define WINPARAMETERS HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nShowCmd
#define INITPARAMETERS hInstance, nShowCmd

class Wnd {
public:
	Wnd();
	Wnd(int _height, int _width, WNDPROC proc, bool(*callback)(), LPCSTR _name);

	HWND GetHandle();
	bool Create(HINSTANCE instanceHandle, int show);
	int Run();
	
private:
	HWND hwnd;
	LPCSTR name;
	int height;
	int width;
	WNDPROC proc;
	bool(*Display)();
};

