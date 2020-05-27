#pragma once
#include"common.h"
#include"gameobject.h"

/* ≤Àµ•ΩÁ√Ê */
class Menu {
public:
	Menu();
	void Run();
private:
	enum MenuButton { B_EASY, B_NORMAL, B_HARD, B_EXIT };
	Buffer buf;
	static const int BUTTON_NUM = 4;
	std::shared_ptr<Button> buttons[BUTTON_NUM];
	int nowActive;
};
