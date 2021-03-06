﻿#define _CRT_SECURE_NO_WARNINGS
#include"common.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

bool getKey[256] = { 0 };
bool keyDown = false;

/* 函数：string 转换 LPCWSTR */
LPCWSTR stringToLPCWSTR(std::string orig) {
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}

bool IsHit(COORD pos1, int wx1, int wy1, COORD pos2, int wx2, int wy2) {
	double startX1 = pos1.X,
		startY1 = pos1.Y,
		endX1 = startX1 + wx1,
		endY1 = startY1 + wy1;
	double startX2 = pos2.X,
		startY2 = pos2.Y,
		endX2 = startX2 + wx2,
		endY2 = startY2 + wy2;
	return !(endY2 <= startY1 || endY1 <= startY2 || startX1 >= endX2 || startX2 >= endX1);
}

bool IsSamePos(COORD pos1, COORD pos2) {
	return pos1.X == pos2.X && pos1.Y == pos2.Y;
}
