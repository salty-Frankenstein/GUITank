#pragma once
#include"common.h"
#include"sprite.h"
#include<string>
#include<iostream>

/* 数字类，游戏中的数字显示 */
class Number :public Sprite {
public:
	Number(int x, int y, int length, double size = 1);
	void Show();
	void Update();
	void Delete();
	void SetNumber(int x);
private:
	int numberNow;
	int numberSet;
	double size;
	const int LENGTH;
	ResourceID image[10];
};
