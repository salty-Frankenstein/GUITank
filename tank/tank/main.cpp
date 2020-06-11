#include"wnd.h"
#include"graphics.h"
#include"game.h"

HWND hwnd;
GFactory gf(hwnd);
Game game(gf);

void init() {
	game.ResourceInit();
}

bool Display() {
	game.GetGFHdl()->BeginDraw();
	game.GetGFHdl()->Clear(_COLOR(Black));
	bool res = game.Run();
	game.GetGFHdl()->EndDraw();
	if (!res)SendMessage(hwnd, WM_CLOSE, 0, 0);
	return true;
}

Wnd myWnd(960, 720, WndProc, Display, "Tank");

int WINAPI WinMain(WINPARAMETERS) {
	if (!myWnd.Create(INITPARAMETERS))
		return 0;
	hwnd = myWnd.GetHandle();
	
	init();
	myWnd.Run();
	game.ClearFile();
	return 0;
}