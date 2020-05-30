#pragma once
#include<d2d1.h>
#include<tchar.h>
#include<windows.h>
#include<wincodec.h>
#include<string>
#include<Dwrite.h>

typedef D2D1_COLOR_F COLOR;
#define _COLOR(COLOR) ( D2D1::ColorF(D2D1::ColorF:: COLOR ) )
#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}

/* point structure */
struct Point {
	float x;
	float y;
	Point(float _x, float _y);
};

/*
class Bitmap
封装WICBitmap && D2DBitmap
*/

class Bitmap {
public:
	Bitmap();
	Bitmap(std::wstring _picname);
	~Bitmap();
	bool Create();
	void Release();
	ID2D1Bitmap* GetBitmap();
	ID2D1Bitmap** GetBitmapPtr();
	IWICFormatConverter* GetConverter();

private:
	ID2D1Bitmap * pBitmap;
	IWICImagingFactory *pIWICFactory;
	IWICBitmapDecoder *pDecoder;
	IWICBitmapFrameDecode *pSource;
	IWICStream *pStream;
	IWICFormatConverter *pConverter;
	IWICBitmapScaler *pScaler;
	std::wstring picname;
};

///////////
/*
class GFactory
封装D2D initializer && ID2D1HwndRenderTarget
工厂类
创建graphics库中其他类的对象
*/

class GFactory {	//as a d2d render target
public:
	GFactory(HWND& _hwndptr);

	ID2D1HwndRenderTarget* GetHandle();		//仅在测试时使用
	ID2D1Factory * GetFactory();			//仅在测试时使用
	bool Create();

	bool CreateBitmap(Bitmap &bmp);

	void BeginDraw();
	bool EndDraw();
	void Clear(COLOR color);

	void DrawBitmap(Bitmap &bmp, float left, float top, float right, float bottom);
	void DrawBitmap(Bitmap &bmp, float left, float top, float right, float bottom, float angle);

private:
	HWND * hwndptr;
	ID2D1Factory * d2dFactory;
	ID2D1HwndRenderTarget* hdl;
};
