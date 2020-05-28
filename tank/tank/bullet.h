#pragma once
#include"sprite.h"
#include"common.h"

const int LAYER_BULLET = 3;
const int BULLET_WIDTH = 10;
const int BULLET_SPEED = 5;
/* 子弹类，可以实例化为玩家或敌人的子弹 */
class Bullet :public Sprite {
public:
	Bullet(SpriteType type, int x, int y, Direction dir);
	void Update();
	void Show();
	void Delete();
	Direction GetDirection()const;
private:
	COORD posLast;
	Direction dir;
	const static int SPEED = 1;
	//const static wchar_t image = L'◆';
	ResourceID image;
};
