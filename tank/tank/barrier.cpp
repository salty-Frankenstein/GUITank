#include"barrier.h"
#include"game.h"
using namespace std;

/* class Barrier */
Barrier::Barrier(int x, int y, SpriteType type, ResourceID id)
	: Sprite(x, y, BARRIER_LAYER, type), image(id) {}

void Barrier::Update() {}

void Barrier::Show() {
	DRAWBITMAP(*resPoolHdl, image, posCur.X, posCur.Y,
		posCur.X + BARRIER_WIDTH, posCur.Y + BARRIER_WIDTH);
}

void Barrier::Delete() {
	del = true;
}

/* class IronWall */
IronWall::IronWall(int x, int y)
	: Barrier(x, y, S_UNDESTORYABLE, BID_IRONWALL) {}

/* class BrickWall */
BrickWall::BrickWall(int x, int y)
	: Barrier(x, y, S_DESTORYABLE, BID_BRICKWALL) {}

/* class WaterWall */
WaterWall::WaterWall(int x, int y)
	: Barrier(x, y, S_ACCESSIBLE, BID_WATERWALL) {}

/* class PlayerBase */
PlayerBase::PlayerBase(int x, int y)
	:Barrier(x, y, S_PLAYER_BASE, BID_PLAYERBASE) {}

void PlayerBase::Show() {
	DRAWBITMAP(*resPoolHdl, image, posCur.X, posCur.Y,
		posCur.X + BARRIER_WIDTH * 3, posCur.Y + BARRIER_WIDTH * 3);
}

void PlayerBase::Delete() {
	del = true;
	Game::state = G_GAMEOVER;
}

/* class bush */
Bush::Bush(int x, int y)
	: Barrier(x, y, S_OTHER, BID_BUSH) {
	layer = 1;
}
