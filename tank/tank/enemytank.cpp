#include"enemytank.h"
#include"game.h"
using namespace std;

const array<array<wchar_t, EnemyTank::WIDTH_X>, EnemyTank::WIDTH_Y> EnemyTank::image = { {
{ L'　',L'█',L'　' },
{ L'█',L'█',L'█' },
{ L'█',L'卐',L'█' }}
};

EnemyTank::EnemyTank(int x, int y, int hp, int damage, int speed, int _shootSpeed)
	: TankBase(S_ENEMY, WIDTH_X, WIDTH_Y, x, y, hp, damage, speed), shootSpeed(_shootSpeed) {}

const array<array<wchar_t, EnemyTank::WIDTH_X>, EnemyTank::WIDTH_Y> EnemyTank::GetImage() {
	return image;
}

void EnemyTank::DrawTank() {
	auto pos = posCur;
	switch (hp) {
	case 1:SetConsoleTextAttribute(GetStdOHdl(), 7); break;
	case 2:SetConsoleTextAttribute(GetStdOHdl(), FOREGROUND_GREEN); break;
	default:SetConsoleTextAttribute(GetStdOHdl(), FOREGROUND_RED); break;
	}
	for (int i = 0; i < WIDTH_Y; i++) {
		SetConsoleCursorPosition(GetStdOHdl(), pos);
		pos.Y++;
		for (int j = 0; j < WIDTH_X; j++) {
			switch (dirCur) {
			case D_UP:
				wcout << (GetImage()[i][j]);
				break;
			case D_DOWN:
				wcout << (GetImage()[WIDTH_Y - i - 1][j]);
				break;
			case D_LEFT:
				wcout << (GetImage()[j][i]);
				break;
			case D_RIGHT:
				wcout << (GetImage()[WIDTH_X - j - 1][i]);
				break;
			}
		}
	}
	SetConsoleTextAttribute(GetStdOHdl(), 7);
}

/* 坦克移动AI */
void EnemyTank::Update() {
	static RandomInt randomInt;

	if (hp <= 0) {
		Delete();
	}
	
	/* 控制速度 */
	if (Game::GetGameTime() % (20 - speed) == 0) {
		posLast = posCur;
		dirLast = dirCur;

		/* 移动 */
		switch (randomInt(1, 20)) {
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
						IsHit(this->GetPos(), 3, 3, s->GetPos(), 1, 1))
						return true;
					if ((IsTank(s) && s.get() != this)
						&& IsHit(this->GetPos(), 3, 3, s->GetPos(), 3, 3))
						return true;
					return false;
				}
			);
			/* 如果有则不移动 */
			if (res != nullptr) {
				posCur = posLast;
			}
		}
	}

	/* 发射子弹 */
	if (Game::GetGameTime() % 10 != 0 && randomInt(1, 30 - shootSpeed) == 1) {
		auto bulPos = posCur;
		switch (dirCur) {
		case D_UP:bulPos.X += 2; break;
		case D_DOWN:bulPos.X += 2; bulPos.Y += 2; break;
		case D_LEFT: bulPos.Y++; break;
		case D_RIGHT:bulPos.X += 4; bulPos.Y++; break;
		}
		/* 如果炮口没有堵上 */
		if (bufferHdl->Any([=](shared_ptr<Sprite> s) {return IsSamePos(bulPos, s->GetPos()); }) == nullptr)
			bufferHdl->Push(make_shared<Bullet>(S_ENEMY_BULLET, bulPos.X, bulPos.Y, dirCur));
	}
}

inline void EnemyTank::GoStraight() {
	switch (dirCur) {
	case D_UP:posCur.Y--; break;
	case D_DOWN:posCur.Y++; break;
	case D_LEFT:posCur.X -= 2; break;
	case D_RIGHT:posCur.X += 2; break;
	}
}

LightTank::LightTank(int x, int y)
	:EnemyTank(x, y, HP, DAMAGE, SPEED, SHOOT_SPEED) {}

const array<array<wchar_t, EnemyTank::WIDTH_X>, EnemyTank::WIDTH_Y> ArmoredCar::image = { {
	{ L'　',L'█',L'　' },
{ L'●',L'█',L'●' },
{ L'●',L'卐',L'●' } }
};

const array<array<wchar_t, EnemyTank::WIDTH_X>, EnemyTank::WIDTH_Y> ArmoredCar::GetImage() {
	return image;
}

ArmoredCar::ArmoredCar(int x, int y)
	: EnemyTank(x, y, HP, DAMAGE, SPEED, SHOOT_SPEED) {}

HeavyTank::HeavyTank(int x, int y)
	: EnemyTank(x, y, HP, DAMAGE, SPEED, SHOOT_SPEED) {}

const array<array<wchar_t, EnemyTank::WIDTH_X>, EnemyTank::WIDTH_Y> AntiTankGun::image = { {
{ L'　',L'█',L'　' },
{ L'※',L'▲',L'※' },
{ L'※',L'卐',L'※' } }
};

const array<array<wchar_t, EnemyTank::WIDTH_X>, EnemyTank::WIDTH_Y> AntiTankGun::GetImage() {
	return image;
}

AntiTankGun::AntiTankGun(int x, int y)
	: EnemyTank(x, y, HP, DAMAGE, SPEED, SHOOT_SPEED) {}
