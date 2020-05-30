#include"tankbase.h"
#include"game.h"
using namespace std;

TankBase::TankBase(SpriteType type, int _widthX, int _widthY,
	int _x, int _y, int _hp, int _damage, int _speed)
	: Sprite(_x, _y, LAYER_TANK, type) {
	widthX = _widthX;
	widthY = _widthY;
	dirCur = D_UP;
	dirLast = D_LEFT;
	posCur.X = posLast.X = _x;
	posCur.Y = posLast.Y = _y;
	hp = _hp;
	damage = _damage;
	speed = _speed;
}

inline void TankBase::Show() {
	DrawTank();
}

void TankBase::Delete() {
	del = true;
	posLast = posCur;
	if (type == S_ENEMY)Game::enemyKill++;
	else {
		Game::player--;
		Game::playerAlive = false;
	}
	//Clean();
	PLAYSOUND(*resPoolHdl, SID_BLAST);
}

int TankBase::GetWidthX()const {
	return widthX;
}

int TankBase::GetWidthY()const {
	return widthY;
}

void TankBase::GetDamage(int damage) {
	hp -= damage;
}
