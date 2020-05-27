#pragma once
#include"common.h"
#include"sprite.h"
#include<string>
#include<iostream>

/* 数字类，游戏中的数字显示 */
class Number :public Sprite {
public:
	Number(int x, int y, int length);
	void Show();
	void Update();
	void Delete();
	void SetNumber(int x);
private:
	int numberNow;
	int numberSet;
	const int LENGTH;
	const static wchar_t image[10][6][4];	//十个数码的图像
};
