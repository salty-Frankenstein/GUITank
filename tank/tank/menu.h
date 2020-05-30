#pragma once
#include"common.h"
#include"gameobject.h"
#include"resourcepool.h"

/* 菜单界面 */
class Menu {
public:
	Menu();
	void Run();
	static ResourcePool* resPoolHdl;
private:
	enum MenuButton { B_EASY, B_NORMAL, B_HARD, B_EXIT };
	Buffer buf;
	static const int BUTTON_NUM = 4;
	static ResourceID cover;
	std::shared_ptr<Button> buttons[BUTTON_NUM];
	int nowActive;
};
