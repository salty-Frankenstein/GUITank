#include"button.h"
#include<iostream>
using namespace std;

Button::Button(int x, int y, string _name)
	:Sprite(x, y) {
	isActive = true;
	name = _name;
}

void Button::Show() {
	SetConsoleCursorPosition(GetStdOHdl(), posCur);
	if (isActive)SetConsoleTextAttribute(GetStdOHdl(), 71);
	else SetConsoleTextAttribute(GetStdOHdl(), 7);
	cout << name;
	SetConsoleTextAttribute(GetStdOHdl(), 7);
}

void Button::Update() {}

void Button::Delete() {
	del = true;
}
