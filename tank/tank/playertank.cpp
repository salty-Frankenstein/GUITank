#include"playertank.h"
#include"game.h"
using namespace std;

const ResourceID PlayerTank::image = BID_PLAYERTANK;

PlayerTank::PlayerTank(int x, int y)
	:TankBase(
		S_PLAYER,
		PLAYERTANK_X, PLAYERTANK_Y,
		x, y,
		PLAYERTANK_HP,
		PLAYERTANK_DAMAGE,
		PLAYERTANK_SPEED) {}

inline void PlayerTank::DrawTank() {
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
	DRAWBITMAP_R(*resPoolHdl, image, posCur.X, posCur.Y, posCur.X + widthX, posCur.Y + widthY, angle);
	//resPoolHdl->gf->DrawBitmap(GETBITMAP(*resPoolHdl, image), 
	//	posCur.X, posCur.Y, posCur.X + widthX, posCur.Y + widthY, angle);
}

inline void PlayerTank::Update() {
	if (hp <= 0) {
		Delete();
	}

	posLast = posCur;
	if (getKey[VK_UP]) { dirCur = D_UP; posCur.Y-= speed;}
	else if (getKey[VK_DOWN]) { dirCur = D_DOWN; posCur.Y += speed; }
	else if (getKey[VK_LEFT]) { dirCur = D_LEFT; posCur.X -= speed; }
	else if (getKey[VK_RIGHT]) { dirCur = D_RIGHT; posCur.X += speed; }

	static GameTime shootTime = 0;
	//发射子弹
	if (getKey['Z']) {
		//连发限制
		auto bulPos = posCur;
		if (!(Game::GetGameTime() - shootTime <= 15)) {
			switch (dirCur) {
			case D_UP:bulPos.X += widthX/2; break;
			case D_DOWN:bulPos.X += widthX/2; bulPos.Y += widthY; break;
			case D_LEFT: bulPos.Y += widthY/2; break;
			case D_RIGHT:bulPos.X += widthX; bulPos.Y += widthY/2; break;
			}
			// 如果炮口没有堵上
			if (bufferHdl->Any([=](shared_ptr<Sprite> s) {return IsSamePos(bulPos, s->GetPos()); }) == nullptr) {
				bufferHdl->Push(make_shared<Bullet>(S_PLAYER_BULLET, bulPos.X, bulPos.Y, dirCur));
				shootTime = Game::GetGameTime();
			}
		}
	}

	if (!IsSamePos(posCur, posLast)) {
		// 判断新位置是否有其他坦克或障碍物
		auto res = bufferHdl->Any(
			[=](shared_ptr<Sprite> s)->bool {
			if (IsBarrier(s->GetType()) &&
				IsHit(this->GetPos(), PLAYERTANK_X, PLAYERTANK_Y, s->GetPos(), BARRIER_WIDTH, BARRIER_WIDTH))
				return true;
			if (s->GetType() == S_ENEMY && 
				IsHit(this->GetPos(), TANK_WIDTH, TANK_WIDTH, s->GetPos(), TANK_WIDTH, TANK_WIDTH))
				return true;
			return false;
		}
		);
		// 如果有则不移动
		if (res != nullptr) {
			posCur = posLast;
		}
	}
	// TODO
	return;

	/*
	posLast = posCur;
	dirLast = dirCur;
	static GameTime shootTime = 0;
	// 键盘事件 
	auto bulPos = posCur;
	if (_kbhit()) {
		switch (_getch()) {
		case 72:
			if (posCur.Y > 1)posCur.Y--;
			dirCur = D_UP;
			break;
		case 75:
			if (posCur.X > 2)posCur.X -= 2;
			dirCur = D_LEFT;
			break;
		case 77:
			if (posCur.X < 2 * (GRID_X - PLAYERTANK_X - 1))posCur.X += 2;
			dirCur = D_RIGHT;
			break;
		case 80:
			if (posCur.Y < GRID_Y - PLAYERTANK_Y - 1)posCur.Y++;
			dirCur = D_DOWN;
			break;
		case 'z':	//发射子弹
			if (Game::GetGameTime() - shootTime <= 5)break;	//连发限制
			switch (dirCur){
			case D_UP:bulPos.X += 2; break;
			case D_DOWN:bulPos.X += 2; bulPos.Y += 2; break;
			case D_LEFT: bulPos.Y++; break;
			case D_RIGHT:bulPos.X += 4; bulPos.Y++; break;
			}
			// 如果炮口没有堵上
			if (bufferHdl->Any([=](shared_ptr<Sprite> s) {return IsSamePos(bulPos, s->GetPos()); }) == nullptr) {
				bufferHdl->Push(make_shared<Bullet>(S_PLAYER_BULLET, bulPos.X, bulPos.Y, dirCur));
				shootTime = Game::GetGameTime();
			}
			break;
		default: break;
		}
	}
	if (!IsSamePos(posCur, posLast)) {
		// 判断新位置是否有其他坦克或障碍物
		auto res = bufferHdl->Any(
			[=](shared_ptr<Sprite> s)->bool {
			if (IsBarrier(s->GetType()) &&
				IsHit(this->GetPos(), 3, 3, s->GetPos(), 1, 1))
				return true;
			if (s->GetType() == S_ENEMY && IsHit(this->GetPos(), 3, 3, s->GetPos(), 3, 3))
				return true;
			return false;
		}
		);
		// 如果有则不移动
		if (res != nullptr) {
			posCur = posLast;
		}
	}
	*/
}
