#include "graphics.h"
#include "common.h"
/* point structure */
Point::Point(float _x, float _y) {
	x = _x;
	y = _y;
}

/* class Bitmap */
Bitmap::Bitmap() {
	pBitmap = NULL;
}

Bitmap::Bitmap(std::wstring _picname) {
	picname = _picname;
	pBitmap = NULL;
}

Bitmap::~Bitmap() {
	SAFE_RELEASE(pBitmap);
}

bool Bitmap::Create() {
	HRESULT hr = S_OK;
	pIWICFactory = NULL;
	pDecoder = NULL;
	pSource = NULL;
	pStream = NULL;
	pConverter = NULL;
	pScaler = NULL;
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&pIWICFactory
	);


	hr = pIWICFactory->CreateDecoderFromFilename(
		picname.c_str(),
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
		if (FAILED(hr)) {
			MessageBox(NULL, _T("Draw 1failed!"), _T("Error"), 0);
			return false;
		}
	}


	if (SUCCEEDED(hr))
	{
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
		if (FAILED(hr)) {
			MessageBox(NULL, _T("Draw 2failed!"), _T("Error"), 0);
			return false;
		}
	}

	hr = pConverter->Initialize(
		pSource,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeMedianCut
	);

	if (FAILED(hr)) {
		MessageBox(NULL, _T("Draw 3failed!"), _T("Error"), 0);
		return false;
	}
	return true;
}

void Bitmap::Release() {
	SAFE_RELEASE(pDecoder);
	SAFE_RELEASE(pSource);
	SAFE_RELEASE(pStream);
	SAFE_RELEASE(pConverter);
	SAFE_RELEASE(pScaler);
}

ID2D1Bitmap* Bitmap::GetBitmap() {
	return pBitmap;
}

ID2D1Bitmap** Bitmap::GetBitmapPtr() {
	return &pBitmap;
}

IWICFormatConverter* Bitmap::GetConverter() {
	return pConverter;
}


/* class GFactory */
GFactory::GFactory(HWND& _hwndptr) {
	hwndptr = &_hwndptr;
}

ID2D1HwndRenderTarget* GFactory::GetHandle() {
	return hdl;
}

ID2D1Factory* GFactory::GetFactory() {
	return d2dFactory;
}

bool GFactory::Create() {
	HRESULT hr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory);
	if (FAILED(hr)) {
		MessageBox(*hwndptr, _T("Create D2D factory failed!"), _T("Error"), 0);
		return false;
	}

	RECT rc;
	GetClientRect(*hwndptr, &rc);
	hr = d2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			*hwndptr,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)
		),
		&hdl
	);
	if (FAILED(hr)) {
		MessageBox(*hwndptr, _T("Create render target failed!"), _T("Error"), 0);
		return false;
	}

	return true;
}

bool GFactory::CreateBitmap(Bitmap &bmp) {
	HRESULT hr;
	hr = hdl->CreateBitmapFromWicBitmap(
		bmp.GetConverter(),
		NULL,
		bmp.GetBitmapPtr()
	);

	if (FAILED(hr)) {
		MessageBox(NULL, _T("Draw 4failed!"), _T("Error"), 0);
		return false;
	}
	bmp.Release();
	return true;
}

void GFactory::BeginDraw() {
	hdl->BeginDraw();
}

bool GFactory::EndDraw() {
	HRESULT hr = hdl->EndDraw();
	if (FAILED(hr)) {
		MessageBox(NULL, _T("Draw failed!"), _T("Error"), 0);
		return false;
	}
	return true;
}

void GFactory::Clear(COLOR color) {	// Clear background color to a color
	hdl->Clear(color);
}

void GFactory::DrawBitmap(Bitmap &bmp, float left, float top, float right, float bottom) {
	hdl->DrawBitmap(
		bmp.GetBitmap(),
		D2D1::RectF(left, top, right, bottom)
	);
}

void GFactory::DrawBitmap(Bitmap &bmp, float left, float top, float right, float bottom, float angle) {
	D2D1::Matrix3x2F oriTransMat;
	hdl->GetTransform(&oriTransMat);
	D2D1_SIZE_F imgSize = bmp.GetBitmap()->GetSize();
	D2D_RECT_F rec1{ left,top,left + imgSize.width,top + imgSize.height };
	ID2D1RectangleGeometry *Grec;
	ID2D1BitmapBrush * brush;
	hdl->CreateBitmapBrush(bmp.GetBitmap(), &brush);
	d2dFactory->CreateRectangleGeometry(rec1, &Grec);
	brush->SetTransform(D2D1::Matrix3x2F::Translation(left, top));
	hdl->SetTransform(
		D2D1::Matrix3x2F::Rotation(angle,
			D2D1::Point2F((rec1.right + rec1.left) / 2, (rec1.top + rec1.bottom) / 2))
		*D2D1::Matrix3x2F::Scale(
			D2D1::Size((right - left) / imgSize.width, (bottom - top) / imgSize.height),
			D2D1::Point2F(left, top))
	);
	hdl->FillGeometry(Grec, brush);
	hdl->SetTransform(oriTransMat);
	SAFE_RELEASE(brush);
}
