#pragma once
#include "tankbase.h"
#include "bullet.h"

/* 长宽 */
const int PLAYERTANK_X = 3;
const int PLAYERTANK_Y = 3;

const int PLAYERTANK_HP = 1;
const int PLAYERTANK_DAMAGE = 1;
const int PLAYERTANK_SPEED = 1;

/* 玩家的坦克 */
class PlayerTank :public TankBase {
public:
	PlayerTank(int x, int y);
	void Update();
	void DrawTank();
private:
	static const wchar_t image[PLAYERTANK_X][PLAYERTANK_Y];
};
