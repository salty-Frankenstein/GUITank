#include"button.h"
#include<iostream>
using namespace std;

Button::Button(int x, int y, int _width, int _height, ResourceID _nameOn, ResourceID _nameOff)
	:Sprite(x, y) {
	isActive = true;
	nameOn = _nameOn;
	nameOff = _nameOff;
	width = _width;
	height = _height;
}

void Button::Show() {
	if (isActive)
		DRAWBITMAP(*resPoolHdl, nameOn, posCur.X, posCur.Y, posCur.X + width, posCur.Y + height);
	else DRAWBITMAP(*resPoolHdl, nameOff, posCur.X, posCur.Y, posCur.X + width, posCur.Y + height);
}

void Button::Update() {}

void Button::Delete() {
	del = true;
}
