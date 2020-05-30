#pragma once
#include"common.h"
#include"sprite.h"
#include"barrier.h"
#include<iostream>
#include<fstream>
#include<string>

const int BACKGROUND_LAYER = 10;

/* 游戏静态背景 */
class Background :public Sprite {
public:
	Background();
	void Show();
	void Update();
	void Draw();	//drawing for borders
	void Delete();
private:
	static ResourceID image;
};
