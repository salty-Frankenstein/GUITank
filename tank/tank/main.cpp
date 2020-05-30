#include"wnd.h"
#include"graphics.h"
#include"dataaccess.h"
#include"sprite.h"
#include"game.h"

HWND hwnd;
GFactory gf(hwnd);
Game game(gf);
Brush b;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KEYDOWN:
		getKey[wParam] = true;
		keyDown = true;
		return 0;

	case WM_KEYUP:
		getKey[wParam] = false;
		keyDown = false;
		return 0;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void init() {
	game.ResourceInit();
	game.GetGFHdl()->CreateBrush(b, _COLOR(Black));
}

bool Display() {
	game.GetGFHdl()->BeginDraw();
	game.GetGFHdl()->Clear(_COLOR(Black));
	//game.GetGFHdl()->DrawLine(b, 1, 1, 200, 200, 1);
	//game.GetGFHdl()->DrawBitmap(GETBITMAP(game.resPool, BID_PLAYERTANK), 1, 1, 100, 100);
	game.TestRun();
	//game.GetGFHdl()->DrawRectangle(b, 1, 1, 100, 100, 2);
	game.GetGFHdl()->EndDraw();
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