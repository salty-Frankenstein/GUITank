#pragma once
#include"common.h"
#include"sprite.h"
#include<string>
#include<vector>

/* 按钮类 */
class Button :public Sprite {
public:
	Button(int x, int y, int width, int height, ResourceID nameOn, ResourceID nameOff);
	void Show();
	void Update();
	void Delete();
	bool isActive;
private:
	int width;
	int height;
	ResourceID nameOn;
	ResourceID nameOff;
};

