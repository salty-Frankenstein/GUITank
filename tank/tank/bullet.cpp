#include"bullet.h"
#include"tankbase.h"
using namespace std;

Bullet::Bullet(SpriteType type, int _x, int _y, Direction _dir)
	:Sprite(_x, _y, LAYER_BULLET, type) {
	dir = _dir;
	posCur.X = posLast.X = _x;
	posCur.Y = posLast.Y = _y;
	if (type == S_PLAYER_BULLET)
		image = BID_PLAYERBULLET;
	else image = BID_ENENYBULLET;
}

void Bullet::Delete() {
	del = true;
	SetConsoleCursorPosition(GetStdOHdl(), posLast);
	wcout << L'　';
}

void Bullet::Update() {
	/* 移动 */
	posLast = posCur;
	switch (dir) {
	case D_UP:posCur.Y -= BULLET_SPEED; break;
	case D_DOWN:posCur.Y += BULLET_SPEED; break;
	case D_LEFT:posCur.X -= BULLET_SPEED; break;
	case D_RIGHT:posCur.X += BULLET_SPEED; break;
	}
	return;
	/* 判断是当前子弹的目标 */
	auto isEnemy = [=](shared_ptr<Sprite> s) -> bool {
		if (s->GetType() == S_PLAYER_BASE)return true;
		if (this->GetType() == S_ENEMY_BULLET) {	//是敌方子弹
			switch (s->GetType()) {
			case S_DESTORYABLE:
			case S_UNDESTORYABLE:
			case S_PLAYER_BULLET:
			case S_PLAYER:
				return true;
			default:
				return false;
			}
		}
		else {	//是玩家子弹
			switch (s->GetType()) {
			case S_DESTORYABLE:
			case S_UNDESTORYABLE:
			case S_ENEMY_BULLET:
			case S_ENEMY:
				return true;
			default:
				return false;
			}
		}
	};

	/* 对于砖墙的命中判定 */
	auto destoryableHit = [=](shared_ptr<Sprite> s) {
		if (s->GetType() != S_DESTORYABLE)return false;
		auto x = this->GetPos(), y = this->GetPos();
		switch (this->GetDirection()) {
		case D_UP:case D_DOWN:x.X -= 2; y.X += 2; break;
		case D_LEFT:case D_RIGHT:x.Y++; y.Y--; break;
		}
		return IsSamePos(this->GetPos(), s->GetPos())	//子弹命中的左右两格也命中
			|| IsSamePos(x, s->GetPos())
			|| IsSamePos(y, s->GetPos());
	};

	/* 判断子弹是否命中游戏对象 */
	auto isHit = [=](shared_ptr<Sprite> s)->bool {
		switch (s->GetType()) {
		case S_PLAYER_BASE:
			return IsHit(this->GetPos(), 1, 1, s->GetPos(), 3, 3);
		case S_ENEMY_BULLET:
		case S_UNDESTORYABLE:
			return IsSamePos(this->GetPos(), s->GetPos());
		case S_DESTORYABLE:
			return destoryableHit(s);
		case S_ENEMY:
		case S_PLAYER:
			auto t = static_cast<TankBase*>(s.get());
			return IsHit(this->GetPos(), 1, 1, t->GetPos(), t->GetWidthX(), t->GetWidthY());
		}
		return false;
	};

	/* 判断对象缓存中是否有对象被命中 */
	auto res = bufferHdl->Any(
		[=](shared_ptr<Sprite> s) -> bool {
			return isEnemy(s) && isHit(s);
		}
	);

	/* 如果被命中 */
	if (res != nullptr) {
		switch (res->GetType()) {
		case S_DESTORYABLE:	//删除被命中的砖墙
			bufferHdl->Map([](shared_ptr<Sprite> s) {s->Delete(); }, destoryableHit);
			break;
		case S_PLAYER_BASE:
		case S_ENEMY_BULLET:
		case S_PLAYER_BULLET:
			res->Delete();	//删除被命中的对象
			break;
		case S_PLAYER:
		case S_ENEMY:
			static_cast<TankBase*>(res.get())->GetDamage(1); break;	//造成1点伤害
		default:break;
		}
		Delete();	//命中后删除子弹
	}
}

void Bullet::Show() {
	if (del)return;
	DRAWBITMAP(*resPoolHdl, image, 
		posCur.X, posCur.Y, posCur.X + BULLET_WIDTH, posCur.Y + BULLET_WIDTH);
	/*
	if(type == S_PLAYER_BULLET)
		SetConsoleTextAttribute(GetStdOHdl(), 14);
	else SetConsoleTextAttribute(GetStdOHdl(), FOREGROUND_RED);
	SetConsoleCursorPosition(GetStdOHdl(), posLast);
	wcout << L'　';
	SetConsoleCursorPosition(GetStdOHdl(), posCur);
	wcout << image;
	SetConsoleTextAttribute(GetStdOHdl(), 7);
	*/
}

Direction Bullet::GetDirection()const {
	return dir;
}
