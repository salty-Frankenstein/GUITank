#pragma once
#include"common.h"
#include"sprite.h"
#include"barrier.h"
#include"number.h"
#include<iostream>
#include<fstream>
#include<string>

/* 游戏静态背景 */
class Background :public Sprite {
public:
	void Show();
	void Update();
	void Draw();	//drawing for borders
	void Delete();
private:
};
