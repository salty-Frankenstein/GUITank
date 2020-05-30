#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
#include <cassert>
using namespace std;

Mode Game::gameMode = M_EASY;
GameTime Game::gameTime = 0;
int Game::player = 0;
int Game::enemyMax = 0;
int Game::enemyNow = 0;
int Game::enemyKill = 0;
bool Game::playerAlive = true;
GameState Game::state = G_MENU;

// TODO
Buffer testBuf;
shared_ptr<Number> testnum = make_shared<Number>(200, 200, 5, 0.8);
Background bg;

Game::Game(GFactory& g) : resPool(g) {
	Sprite::resPoolHdl = &resPool;
	// TODO
	Sprite::bufferHdl = &testBuf;
}

void Game::ResourceInit() {
	resPool.ResourceInit();
	testBuf.Push(make_shared<PlayerTank>(15, 15));
	testBuf.Push(make_shared<BrickWall>(100, 100));
	testBuf.Push(make_shared<WaterWall>(125, 125));
	testBuf.Push(make_shared<HeavyTank>(150, 150));
	testBuf.Push(testnum);
	bg.Draw();
	//testBuf.Push(make_shared<Bullet>(S_PLAYER_BULLET, 100, 100, D_RIGHT));
}

/*
shared_ptr<Bitmap> Game::GetBitmapHdl(ResourceID id) {
	assert(id < resPool.bmp.size() &&  id >= 0);
	return resPool.bmp[id];
}
*/

void Game::TestRun() {
	Game::gameTime++;
	testnum->SetNumber(Game::gameTime);
	testBuf.Update();
	testBuf.Show();
}

void Game::Run() {
	//system("cls");
	bool win = true;
	/* 游戏主流程状态机 */
	while (state != G_EXIT) {
		switch (state) {
		case G_MENU:
			menu.Run();
			break;
		case G_GAME:
			for (int stage = 1; stage <= MAX_STAGE; stage++) {
				stagePtr = make_shared<Stage>(stage, gameMode);
				if (!stagePtr->Run()) {
					win = false;
					break;
				}
			}
			if (win)state = G_WIN;
			else state = G_GAMEOVER;
			break;
		case G_GAMEOVER:
			SetFontSize(18);
			system("cls");
			DrawTitle({ 10,10 }, GAMEOVER_PATH);
			cout << "press any key to return" << endl;
			_getch();
			state = G_MENU;
			break;
		case G_WIN:
			SetFontSize(18);
			system("cls");
			DrawTitle({ 10,10 }, WIN_PATH);
			cout << "press any key to return" << endl;
			_getch();
			state = G_MENU;
			break;
		default:break;
		}
	}
}

GameTime Game::GetGameTime() {
	return gameTime;
}

void Game::AddGameTime() {
	gameTime++;
}

GFactory* Game::GetGFHdl() {
	return resPool.gf;
}

void Game::ClearFile() {
	resPool.ResourceClear();
	resPool.dao->ClearFile();
}
