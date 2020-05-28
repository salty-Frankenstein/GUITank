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
	SetConsoleCursorPosition(GetStdOHdl(), posCur);
	wcout << L'　';
}

/* class IronWall */
IronWall::IronWall(int x, int y)
	: Barrier(x, y, S_UNDESTORYABLE, BID_IRONWALL) {}

/* class BrickWall */
BrickWall::BrickWall(int x, int y)
	: Barrier(x, y, S_DESTORYABLE, BID_BRICKWALL) {}

/*
void BrickWall::Show() {
	if (Game::GetGameTime() % REDRAW != 0)return;
	SetConsoleTextAttribute(GetStdOHdl(), 96);
	SetConsoleCursorPosition(GetStdOHdl(), posCur);
	wcout << L"＋";
	SetConsoleTextAttribute(GetStdOHdl(), 7);
}
*/

/* class WaterWall */
WaterWall::WaterWall(int x, int y)
	: Barrier(x, y, S_ACCESSIBLE, BID_WATERWALL) {}

/*
void WaterWall::Show() {
	if (Game::GetGameTime() % 2 != 0)return;
	SetConsoleTextAttribute(GetStdOHdl(), 151);
	SetConsoleCursorPosition(GetStdOHdl(), posCur);
	wcout << L"≈";
	SetConsoleTextAttribute(GetStdOHdl(), 7);
}
*/

/* class PlayerBase */
PlayerBase::PlayerBase(int x, int y)
	:Barrier(x, y, S_PLAYER_BASE, BID_PLAYERBASE) {}

void PlayerBase::Show() {
	auto pos = posCur;
	if (Game::GetGameTime() % REDRAW != 0)return;
	SetConsoleCursorPosition(GetStdOHdl(), pos);
	wcout << L"　◇　";
	pos.Y++;
	SetConsoleCursorPosition(GetStdOHdl(), pos);
	wcout << L"◆○◆";
	pos.Y++;
	SetConsoleCursorPosition(GetStdOHdl(), pos);
	wcout << L"　◇　";
}

void PlayerBase::Delete() {
	del = true;
	auto pos = posCur;
	for (int i = 1; i <= 3; i++) {
		SetConsoleCursorPosition(GetStdOHdl(), pos);
		wcout << L"　　　";
		pos.Y++;
	}
	Game::state = G_GAMEOVER;
}
