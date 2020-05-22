#include"wnd.h"
#include"graphics.h"
#include"dataaccess.h"
HWND hwnd;
bool getKey[256] = { 0 };
bool keyDown = false;

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

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


DataAccess* dao = new NormalDataAccess();
//DataAccess* dao = new CompressedDataAccess(".\\", "src");
GFactory gf(hwnd);
Brush b;
Bitmap* bmp;

void init() {
	gf.Create();
	gf.CreateBrush(b, _COLOR(Black));
	bmp = new Bitmap(dao->GetFile(".\\src\\1.bmp"));
	bmp->Create();
	gf.CreateBitmap(*bmp);
	
}

bool Display() {
	gf.BeginDraw();
	gf.Clear(_COLOR(White));
	gf.DrawLine(b, 1, 1, 200, 200, 1);
	gf.DrawBitmap(*bmp, 1, 1, 100, 100);
	gf.EndDraw();
	return true;
}

Wnd myWnd(800, 600, WndProc, Display, "hello");

int WINAPI WinMain(WINPARAMETERS) {
	if (!myWnd.Create(INITPARAMETERS))
		return 0;
	hwnd = myWnd.GetHandle();
	
	init();
	myWnd.Run();
	delete bmp;
	dao->ClearFile();
	return 0;
}