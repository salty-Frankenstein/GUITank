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
	//do the cleaning
	/*
	if (IsSamePos(posCur,posLast) && dirLast == dirCur
		&& Game::GetGameTime()%REDRAW != 0)return;
	Clean();
	*/
	//draw a new frame
	DrawTank();
}

void TankBase::Clean() {
	/*
	auto pos = posLast;
	if (dirCur == D_UP || dirCur == D_DOWN) {
		for (int i = 1; i <= widthY; i++) {
			SetConsoleCursorPosition(GetStdOHdl(), pos);
			pos.Y++;
			for (int j = 1; j <= widthX; j++)
				wcout << L'　';
		}
	}
	else {
		for (int i = 1; i <= widthX; i++) {
			SetConsoleCursorPosition(GetStdOHdl(), pos);
			pos.Y++;
			for (int j = 1; j <= widthY; j++)
				wcout << L'　';
		}
	}
	*/
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
