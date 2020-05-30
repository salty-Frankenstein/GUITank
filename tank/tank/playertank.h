#pragma once
#include "tankbase.h"
#include "bullet.h"

/* 长宽 */
const int PLAYERTANK_X = TANK_WIDTH;
const int PLAYERTANK_Y = TANK_WIDTH;

const int PLAYERTANK_HP = 1;
const int PLAYERTANK_DAMAGE = 1;
const int PLAYERTANK_SPEED = 3;

/* 玩家的坦克 */
class PlayerTank :public TankBase {
public:
	PlayerTank(int x, int y);
	void Update();
	void DrawTank();
private:
	static const ResourceID image;
};
