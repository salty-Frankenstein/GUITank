﻿#include"enemytank.h"
#include"game.h"
using namespace std;

EnemyTank::EnemyTank(int x, int y, int hp, int damage, int speed, int _shootSpeed)
	: TankBase(S_ENEMY, WIDTH_X, WIDTH_Y, x, y, hp, damage, speed), shootSpeed(_shootSpeed) {
	image = BID_LIGHT;
}

ResourceID EnemyTank::GetImage() {
	return image;
}

void EnemyTank::DrawTank() {
	float angle;

	switch (dirCur)
	{
	case D_UP:
		angle = 0;
		break;
	case D_DOWN:
		angle = 180;
		break;
	case D_LEFT:
		angle = 270;
		break;
	case D_RIGHT:
		angle = 90;
		break;
	}
	DRAWBITMAP_R(*resPoolHdl, GetImage(), posCur.X, posCur.Y, posCur.X + widthX, posCur.Y + widthY, angle);
}

/* 坦克移动AI */
void EnemyTank::Update() {
	static RandomInt randomInt;

	if (hp <= 0) {
		Delete();
		return;
	}

	posLast = posCur;
	dirLast = dirCur;

	/* 移动 */
	switch (randomInt(1, 150)) {
	case 1:dirCur = D_UP; break;
	case 2:dirCur = D_LEFT; break;
	case 3:dirCur = D_RIGHT; break;
	case 4:dirCur = D_DOWN; break;
	default:GoStraight(); break;
	}

	/* 如果移动位置 */
	if (!IsSamePos(posCur, posLast)) {
		/* 判断新位置是否有其他坦克或障碍物 */
		auto res = bufferHdl->Any(
			[=](shared_ptr<Sprite> s)->bool {
			if (IsBarrier(s->GetType()) &&
				IsHit(this->GetPos(), TANK_WIDTH, TANK_WIDTH, 
					s->GetPos(), BARRIER_WIDTH, BARRIER_WIDTH))
				return true;
			if ((IsTank(s) && s.get() != this)
				&& IsHit(this->GetPos(), TANK_WIDTH, TANK_WIDTH,
					s->GetPos(), TANK_WIDTH, TANK_WIDTH))
				return true;
			return false;
		}
		);
		/* 如果有则不移动 */
		if (res != nullptr) {
			posCur = posLast;
		}
	}

	/* 发射子弹 */
	if (Game::GetGameTime() % 10 == 0 && randomInt(1, 20 - shootSpeed) == 1) {
		auto bulPos = posCur;
		switch (dirCur) {
		case D_UP:bulPos.X += widthX / 2 - 5; break;
		case D_DOWN:bulPos.X += widthX / 2 - 5; bulPos.Y += widthY; break;
		case D_LEFT: bulPos.Y += widthY / 2 - 5; break;
		case D_RIGHT:bulPos.X += widthX; bulPos.Y += widthY / 2 - 5; break;
		}
		bufferHdl->Push(make_shared<Bullet>(S_ENEMY_BULLET, bulPos.X, bulPos.Y, dirCur));
	}

}

inline void EnemyTank::GoStraight() {
	switch (dirCur) {
	case D_UP:posCur.Y -= speed; break;
	case D_DOWN:posCur.Y += speed; break;
	case D_LEFT:posCur.X -= speed; break;
	case D_RIGHT:posCur.X += speed; break;
	}
}

LightTank::LightTank(int x, int y)
	:EnemyTank(x, y, HP, DAMAGE, SPEED, SHOOT_SPEED) {}

ArmoredCar::ArmoredCar(int x, int y)
	: EnemyTank(x, y, HP, DAMAGE, SPEED, SHOOT_SPEED) {
	imageG = BID_ARMORED_G;
	imageB = BID_ARMORED_B;
}

ResourceID ArmoredCar::GetImage() {
	if (hp == 2)return imageG;
	return imageB;
}

HeavyTank::HeavyTank(int x, int y)
	: EnemyTank(x, y, HP, DAMAGE, SPEED, SHOOT_SPEED) {
	imageR = BID_HEAVY_R;
	imageG = BID_HEAVY_G;
	imageB = BID_HEAVY_B;
}

ResourceID HeavyTank::GetImage() {
	if (hp == 3)return imageR;
	if (hp == 2)return imageG;
	return imageB;
}

ResourceID AntiTankGun::GetImage() {
	return image;
}

AntiTankGun::AntiTankGun(int x, int y)
	: EnemyTank(x, y, HP, DAMAGE, SPEED, SHOOT_SPEED) {
	image = BID_ANTI;
}
