#include"barrier.h"
#include"game.h"
using namespace std;

/* class Barrier */
Barrier::Barrier(int x, int y, SpriteType type)
	: Sprite(x, y, BARRIER_LAYER, type) {}

void Barrier::Update() {}

void Barrier::Delete() {
	del = true;
	SetConsoleCursorPosition(GetStdOHdl(), posCur);
	wcout << L'　';
}

/* class IronWall */
IronWall::IronWall(int x, int y)
	: Barrier(x, y, S_UNDESTORYABLE) {}

void IronWall::Show() {
	if (Game::GetGameTime() % REDRAW != 0)return;
	SetConsoleTextAttribute(GetStdOHdl(), 143);
	SetConsoleCursorPosition(GetStdOHdl(), posCur);
	wcout << L'■';
	SetConsoleTextAttribute(GetStdOHdl(), 7);
}

/* class BrickWall */
BrickWall::BrickWall(int x, int y)
	: Barrier(x, y, S_DESTORYABLE) {}

void BrickWall::Show() {
	if (Game::GetGameTime() % REDRAW != 0)return;
	SetConsoleTextAttribute(GetStdOHdl(), 96);
	SetConsoleCursorPosition(GetStdOHdl(), posCur);
	wcout << L"＋";
	SetConsoleTextAttribute(GetStdOHdl(), 7);
}

/* class WaterWall */
WaterWall::WaterWall(int x, int y)
	: Barrier(x, y, S_ACCESSIBLE) {}

void WaterWall::Show() {
	if (Game::GetGameTime() % 2 != 0)return;
	SetConsoleTextAttribute(GetStdOHdl(), 151);
	SetConsoleCursorPosition(GetStdOHdl(), posCur);
	wcout << L"≈";
	SetConsoleTextAttribute(GetStdOHdl(), 7);
}

/* class PlayerBase */
PlayerBase::PlayerBase(int x, int y)
	:Barrier(x, y, S_PLAYER_BASE) {}

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
