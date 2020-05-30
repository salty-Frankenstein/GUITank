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
}

inline void PlayerTank::Update() {
	if (hp <= 0) {
		Delete();
		return;
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
			case D_UP:bulPos.X += widthX / 2 - 5; break;
			case D_DOWN:bulPos.X += widthX / 2 - 5; bulPos.Y += widthY; break;
			case D_LEFT: bulPos.Y += widthY / 2 - 5; break;
			case D_RIGHT:bulPos.X += widthX; bulPos.Y += widthY / 2 - 5; break;
			}
			// 如果炮口没有堵上
			if (bufferHdl->Any([=](shared_ptr<Sprite> s) {return IsSamePos(bulPos, s->GetPos()); }) == nullptr) {
				bufferHdl->Push(make_shared<Bullet>(S_PLAYER_BULLET, bulPos.X, bulPos.Y, dirCur));
				PLAYSOUND(*resPoolHdl, SID_FIRE);
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

}
